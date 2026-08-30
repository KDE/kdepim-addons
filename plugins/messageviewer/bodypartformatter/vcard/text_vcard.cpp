/*

  This file is part of KMail, the KDE mail client.
  SPDX-FileCopyrightText: 2004 Till Adam <adam@kde.org>
  SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updatecontactjob.h"
#include "vcard_debug.h"
#include "vcardmemento.h"

#include <KContacts/Addressee>
#include <KContacts/VCardConverter>

#include <MessageViewer/BodyPartURLHandler>
#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/NodeHelper>
#include <qnamespace.h>
using MimeTreeParser::Interface::BodyPart;

#include <Akonadi/AddContactJob>

#include <Akonadi/ContactViewer>
#include <Akonadi/StandardContactFormatter>
#include <MessageViewer/IconNameCache>

#include <KIO/FileCopyJob>
#include <KIO/StatJob>
#include <KIconLoader>
#include <KLocalizedString>

#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMimeDatabase>
#include <QTemporaryFile>
using namespace Qt::Literals::StringLiterals;

namespace
{
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    Formatter() = default;

    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *writer, MessageViewer::RenderContext *) const override
    {
        QMimeDatabase db;
        auto mt = db.mimeTypeForName(QString::fromLatin1(msgPart->content()->contentType()->mimeType().toLower()));
        if (!mt.isValid() || mt.name() != QLatin1StringView("text/vcard")) {
            return false;
        }

        const QString vCard = msgPart->text();
        if (vCard.isEmpty()) {
            return false;
        }

        KContacts::VCardConverter vcc;

        auto memento = dynamic_cast<MessageViewer::VcardMemento *>(msgPart->memento());

        const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
        // The email list is indexed by the position in the addressee list: an addressee without
        // email keeps its slot, so that the memento stays in sync with the vcards rendered below
        // and with the indexes used in the generated links.
        QStringList lst;
        lst.reserve(al.count());
        // Number of non-empty addressees, and of those which can be looked up in the address book
        int count = 0;
        int emailCount = 0;
        for (const KContacts::Addressee &a : al) {
            if (a.isEmpty()) {
                lst.append(QString());
                continue;
            }
            const QStringList emails = a.emails();
            lst.append(emails.isEmpty() ? QString() : emails.constFirst());
            if (!emails.isEmpty()) {
                emailCount++;
            }
            count++;
        }
        if (!emailCount) {
            return false;
        }

        writer->write(u"<div align=\"center\"><h2>"_s + i18np("Attached business card", "Attached business cards", count) + u"</h2></div>"_s);

        const QString defaultPixmapPath = MessageViewer::IconNameCache::instance()->iconPath(u"user-identity"_s, KIconLoader::Desktop);
        const QString defaultMapIconPath = MessageViewer::IconNameCache::instance()->iconPath(u"map-symbolic"_s, KIconLoader::Small);
        const QString defaultSmsIconPath = MessageViewer::IconNameCache::instance()->iconPath(u"message-new"_s, KIconLoader::Small);
        QMap<QString, QString> mapImppIcons;
        for (const auto &imppService : KContacts::Impp::serviceTypes()) {
            const QString iconName = KContacts::Impp::serviceIcon(imppService);
            mapImppIcons.insert(iconName, MessageViewer::IconNameCache::instance()->iconPath(iconName, KIconLoader::Small));
        }
        if (!memento) {
            memento = new MessageViewer::VcardMemento(lst);
            msgPart->setMemento(memento);

            auto nodeHelper = msgPart->nodeHelper();
            if (nodeHelper) {
                QObject::connect(memento, &MessageViewer::VcardMemento::update, nodeHelper, &MimeTreeParser::NodeHelper::update);
            }
        }

        for (int index = 0, total = al.count(); index < total; ++index) {
            const KContacts::Addressee &a = al.at(index);
            if (a.isEmpty()) {
                continue;
            }
            Akonadi::StandardContactFormatter formatter;
            formatter.setContact(a);
            formatter.setDisplayQRCode(false);
            QString htmlStr = formatter.toHtml(Akonadi::StandardContactFormatter::EmbeddableForm);
            const KContacts::Picture photo = a.photo();
            htmlStr.replace(u"<img src=\"map_icon\""_s, u"<img src=\"%1\" width=\"16\" height=\"16\""_s.arg(defaultMapIconPath));
            htmlStr.replace(u"<img src=\"sms_icon\""_s, u"<img src=\"%1\" width=\"16\" height=\"16\""_s.arg(defaultSmsIconPath));
            for (const auto &[key, value] : mapImppIcons.asKeyValueRange()) {
                htmlStr.replace(u"<img src=\"%1\""_s.arg(key), u"<img src=\"%1\" width=\"16\" height=\"16\""_s.arg(value));
            }
            if (photo.isEmpty()) {
                htmlStr.replace(u"img src=\"contact_photo\""_s, u"img src=\"%1\""_s.arg(defaultPixmapPath));
            } else {
                QImage img = a.photo().data();
                const QString dir = msgPart->nodeHelper()->createTempDir(QLatin1StringView("vcard-") + a.uid());
                const QString filename = dir + QLatin1Char('/') + a.uid();
                img.save(filename, "PNG");
                msgPart->nodeHelper()->addTempFile(filename);
                const QString href = QLatin1StringView("file:") + QLatin1StringView(QUrl::toPercentEncoding(filename));
                htmlStr.replace(QLatin1StringView("img src=\"contact_photo\""), u"img src=\"%1\""_s.arg(href));
            }
            writer->write(htmlStr);

            if (!memento || !memento->finished() || (memento->finished() && !memento->vcardExist(index))) {
                const QString addToLinkText = i18n("[Add this contact to the address book]");
                QString op = u"addToAddressBook:%1"_s.arg(index);
                writer->write(u"<div align=\"center\"><a href=\""_s + msgPart->makeLink(op) + u"\">"_s + addToLinkText + u"</a></div><br/><br/>"_s);
            } else {
                if (memento->address(index) != a) {
                    const QString addToLinkText = i18n("[Update this contact in the address book]");
                    const QString op = u"updateToAddressBook:%1"_s.arg(index);
                    writer->write(u"<div align=\"center\"><a href=\""_s + msgPart->makeLink(op) + u"\">"_s + addToLinkText + u"</a></div><br><br>"_s);
                } else {
                    const QString addToLinkText = i18n("[This contact is already in addressbook]");
                    writer->write(u"<div align=\"center\">"_s + addToLinkText + u"</a></div><br><br>"_s);
                }
            }
        }

        return true;
    }
};

class UrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    [[nodiscard]] QString name() const override
    {
        return u"vcardhandler"_s;
    }

    bool handleClick(MessageViewer::Viewer *viewerInstance, BodyPart *bodyPart, const QString &path) const override
    {
        Q_UNUSED(viewerInstance)
        const QString vCard = bodyPart->content()->decodedText();
        if (vCard.isEmpty()) {
            return true;
        }
        KContacts::VCardConverter vcc;
        const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
        const int index = QStringView(path).right(path.length() - path.lastIndexOf(QLatin1Char(':')) - 1).toInt();
        if (index == -1 || index >= al.count()) {
            return true;
        }
        const KContacts::Addressee a = al.at(index);
        if (a.isEmpty()) {
            return true;
        }

        if (path.startsWith(QLatin1StringView("addToAddressBook"))) {
            auto job = new Akonadi::AddContactJob(a, nullptr);
            job->start();
        } else if (path.startsWith(QLatin1StringView("updateToAddressBook"))) {
            const QStringList emails = a.emails();
            if (emails.isEmpty()) {
                return true;
            }
            auto job = new UpdateContactJob(emails.constFirst(), a, nullptr);
            job->start();
        }

        return true;
    }

    static KContacts::Addressee findAddressee(BodyPart *part, const QString &path)
    {
        const QString vCard = part->content()->decodedText();
        if (!vCard.isEmpty()) {
            KContacts::VCardConverter vcc;
            const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
            const int index = QStringView(path).right(path.length() - path.lastIndexOf(QLatin1Char(':')) - 1).toInt();
            if (index >= 0 && index < al.count()) {
                return al.at(index);
            }
        }
        return {};
    }

    bool handleContextMenuRequest(BodyPart *part, const QString &path, const QPoint &point) const override
    {
        const QString vCard = part->content()->decodedText();
        if (vCard.isEmpty()) {
            return true;
        }
        KContacts::Addressee a = findAddressee(part, path);
        if (a.isEmpty()) {
            return true;
        }

        auto menu = new QMenu();
        QAction *open = menu->addAction(QIcon::fromTheme(u"document-open"_s), i18n("View Business Card"));
        QAction *saveas = menu->addAction(QIcon::fromTheme(u"document-save-as"_s), i18n("Save Business Card As…"));

        QAction *action = menu->exec(point, nullptr);
        if (action == open) {
            openVCard(a, vCard);
        } else if (action == saveas) {
            saveAsVCard(a, vCard);
        }
        delete menu;
        return true;
    }

    QString statusBarMessage(BodyPart *part, const QString &path) const override
    {
        KContacts::Addressee a = findAddressee(part, path);
        const bool addToAddressBook = path.startsWith(QLatin1StringView("addToAddressBook"));
        if (a.realName().isEmpty()) {
            return addToAddressBook ? i18n("Add this contact to the address book.") : i18n("Update this contact to the address book.");
        } else {
            return addToAddressBook ? i18n("Add \"%1\" to the address book.", a.realName()) : i18n("Update \"%1\" to the address book.", a.realName());
        }
    }

    [[nodiscard]] bool openVCard(const KContacts::Addressee &a, const QString &vCard) const
    {
        Q_UNUSED(vCard)
        auto view = new Akonadi::ContactViewer(nullptr);
        view->setAttribute(Qt::WA_DeleteOnClose);
        view->setRawContact(a);
        view->setMinimumSize(300, 400);
        view->show();
        return true;
    }

    [[nodiscard]] bool saveAsVCard(const KContacts::Addressee &a, const QString &vCard) const
    {
        QString fileName;
        const QString givenName(a.givenName());
        if (givenName.isEmpty()) {
            fileName = a.familyName() + u".vcf"_s;
        } else {
            fileName = givenName + QLatin1Char('_') + a.familyName() + u".vcf"_s;
        }
        // get the saveas file name
        QUrl saveAsUrl = QFileDialog::getSaveFileUrl(nullptr, i18nc("@title:window", "Save Business Card"), QUrl::fromUserInput(fileName));
        if (saveAsUrl.isEmpty()) {
            return false;
        }

        // put the attachment in a temporary file and save it
        QTemporaryFile tmpFile;
        if (!tmpFile.open()) {
            qCWarning(VCARD_LOG) << "Impossible to create temporary file";
            return false;
        }

        QByteArray data = vCard.toUtf8();
        tmpFile.write(data);
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), saveAsUrl, -1, KIO::Overwrite);
        return job->exec();
    }
};

class Plugin : public QObject, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "text_vcard.json")
public:
    [[nodiscard]] std::unique_ptr<MessageViewer::MessagePartRendererBase> renderer(int index) override
    {
        return validIndex(index) ? std::make_unique<Formatter>() : nullptr;
    }

    [[nodiscard]] const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override
    {
        return validIndex(idx) ? new UrlHandler() : nullptr;
    }

private:
    [[nodiscard]] bool validIndex(int idx) const
    {
        return idx == 0;
    }
};
}

#include "text_vcard.moc"
