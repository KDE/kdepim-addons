/*

  This file is part of KMail, the KDE mail client.
  Copyright (c) 2004 Till Adam <adam@kde.org>
  Copyright (c) 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
  Copyright (C) 2012-2017 Laurent Montel <montel@kde.org>

  KMail is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  KMail is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  In addition, as a special exception, the copyright holders give
  permission to link the code of this program with any edition of
  the Qt library by Trolltech AS, Norway (or with modified versions
  of Qt that use the same license as Qt), and distribute linked
  combinations including the two.  You must obey the GNU General
  Public License in all respects for all of the code used other than
  Qt.  If you modify this file, you may extend this exception to
  your version of the file, but you are not obligated to do so.  If
  you do not wish to do so, delete this exception statement from
  your version.
*/

#include "updatecontactjob.h"
#include "vcardmemento.h"

#include <KContacts/VCardConverter>
#include <KContacts/Addressee>


#include <MessageViewer/BodyPartURLHandler>
#include <MimeTreeParser/BodyPartFormatter>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>
#include <MimeTreeParser/HtmlWriter>
using MimeTreeParser::Interface::BodyPart;

#include <LibkdepimAkonadi/AddContactJob>

#include <Akonadi/Contact/ContactViewer>
#include <Akonadi/Contact/StandardContactFormatter>


#include <KLocalizedString>
#include <KIconLoader>

#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QTemporaryFile>
#include <KIO/StatJob>
#include <KIO/FileCopyJob>
#include "vcard_debug.h"

namespace {
class Formatter : public MimeTreeParser::Interface::BodyPartFormatter
{
public:
    Formatter()
    {
    }

    Result format(MimeTreeParser::Interface::BodyPart *bodyPart, MimeTreeParser::HtmlWriter *writer) const override
    {
        if (!writer) {
            return Ok;
        }

        const QString vCard = bodyPart->asText();
        if (vCard.isEmpty()) {
            return AsIcon;
        }

        KContacts::VCardConverter vcc;

        MessageViewer::VcardMemento *memento = dynamic_cast<MessageViewer::VcardMemento *>(bodyPart->memento());
        QStringList lst;

        // Pre-count the number of non-empty addressees
        int count = 0;
        const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
        for (const KContacts::Addressee &a : al) {
            if (a.isEmpty()) {
                continue;
            }
            if (!memento) {
                if (!a.emails().isEmpty()) {
                    lst.append(a.emails().first());
                    count++;
                }
            }
        }
        if (!count) {
            return AsIcon;
        }

        writer->write(QStringLiteral("<div align=\"center\"><h2>")
                      +i18np("Attached business card", "Attached business cards", count)
                      +QStringLiteral("</h2></div>"));

        count = 0;
        static QString defaultPixmapPath = QUrl::fromLocalFile(KIconLoader::global()->iconPath(QStringLiteral("user-identity"), KIconLoader::Desktop)).url();
        static QString defaultMapIconPath = QUrl::fromLocalFile(KIconLoader::global()->iconPath(QStringLiteral("document-open-remote"), KIconLoader::Small)).url();

        if (!memento) {
            MessageViewer::VcardMemento *memento = new MessageViewer::VcardMemento(lst);
            bodyPart->setBodyPartMemento(memento);

            auto nodeHelper = bodyPart->nodeHelper();
            if (nodeHelper) {
                QObject::connect(memento, &MessageViewer::VcardMemento::update,
                                 nodeHelper, &MimeTreeParser::NodeHelper::update);
            }
        }

        for (const KContacts::Addressee &a : al) {
            if (a.isEmpty()) {
                continue;
            }
            Akonadi::StandardContactFormatter formatter;
            formatter.setContact(a);
            formatter.setDisplayQRCode(false);
            QString htmlStr = formatter.toHtml(Akonadi::StandardContactFormatter::EmbeddableForm);
            const KContacts::Picture photo = a.photo();
            htmlStr.replace(QStringLiteral("<img src=\"map_icon\""), QStringLiteral("<img src=\"%1\"").arg(defaultMapIconPath));
            if (photo.isEmpty()) {
                htmlStr.replace(QStringLiteral("img src=\"contact_photo\""), QStringLiteral("img src=\"%1\"").arg(defaultPixmapPath));
            } else {
                QImage img = a.photo().data();
                const QString dir = bodyPart->nodeHelper()->createTempDir(QStringLiteral("vcard-") + a.uid());
                const QString filename = dir + QDir::separator() + a.uid();
                img.save(filename, "PNG");
                bodyPart->nodeHelper()->addTempFile(filename);
                const QString href = QStringLiteral("file:") + QLatin1String(QUrl::toPercentEncoding(filename));
                htmlStr.replace(QLatin1String("img src=\"contact_photo\""), QStringLiteral("img src=\"%1\"").arg(href));
            }
            writer->write(htmlStr);

            if (!memento
                || (memento && !memento->finished())
                || (memento && memento->finished() && !memento->vcardExist(count))) {
                const QString addToLinkText = i18n("[Add this contact to the address book]");
                QString op = QStringLiteral("addToAddressBook:%1").arg(count);
                writer->write(QStringLiteral("<div align=\"center\"><a href=\"")
                              +bodyPart->makeLink(op)
                              +QStringLiteral("\">")
                              +addToLinkText
                              +QStringLiteral("</a></div><br><br>"));
            } else {
                if (memento->address(count) != a) {
                    const QString addToLinkText = i18n("[Update this contact to the address book]");
                    const QString op = QStringLiteral("updateToAddressBook:%1").arg(count);
                    writer->write(QStringLiteral("<div align=\"center\"><a href=\"")
                                  +bodyPart->makeLink(op)
                                  +QStringLiteral("\">")
                                  +addToLinkText
                                  +QStringLiteral("</a></div><br><br>"));
                } else {
                    const QString addToLinkText = i18n("[This contact is already in addressbook]");
                    writer->write(QStringLiteral("<div align=\"center\">")
                                  +addToLinkText
                                  +QStringLiteral("</a></div><br><br>"));
                }
            }
            count++;
        }

        return Ok;
    }
};

class UrlHandler : public MimeTreeParser::Interface::BodyPartURLHandler
{
public:
    bool handleClick(MessageViewer::Viewer *viewerInstance, BodyPart *bodyPart, const QString &path) const override
    {
        Q_UNUSED(viewerInstance);
        const QString vCard = bodyPart->asText();
        if (vCard.isEmpty()) {
            return true;
        }
        KContacts::VCardConverter vcc;
        const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
        const int index = path.rightRef(path.length() - path.lastIndexOf(QLatin1Char(':')) - 1).toInt();
        if (index == -1 || index >= al.count()) {
            return true;
        }
        const KContacts::Addressee a = al.at(index);
        if (a.isEmpty()) {
            return true;
        }

        if (path.startsWith(QStringLiteral("addToAddressBook"))) {
            KPIM::AddContactJob *job = new KPIM::AddContactJob(a, nullptr);
            job->start();
        } else if (path.startsWith(QStringLiteral("updateToAddressBook"))) {
            UpdateContactJob *job = new UpdateContactJob(a.emails().first(), a, nullptr);
            job->start();
        }

        return true;
    }

    static KContacts::Addressee findAddressee(BodyPart *part, const QString &path)
    {
        const QString vCard = part->asText();
        if (!vCard.isEmpty()) {
            KContacts::VCardConverter vcc;
            const KContacts::Addressee::List al = vcc.parseVCards(vCard.toUtf8());
            const int index = path.rightRef(path.length() - path.lastIndexOf(QLatin1Char(':')) - 1).toInt();
            if (index >= 0 && index < al.count()) {
                return al.at(index);
            }
        }
        return KContacts::Addressee();
    }

    bool handleContextMenuRequest(BodyPart *part, const QString &path, const QPoint &point) const override
    {
        const QString vCard = part->asText();
        if (vCard.isEmpty()) {
            return true;
        }
        KContacts::Addressee a = findAddressee(part, path);
        if (a.isEmpty()) {
            return true;
        }

        QMenu *menu = new QMenu();
        QAction *open
            = menu->addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("View Business Card"));
        QAction *saveas
            = menu->addAction(QIcon::fromTheme(QStringLiteral("document-save-as")), i18n("Save Business Card As..."));

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
        const bool addToAddressBook = path.startsWith(QStringLiteral("addToAddressBook"));
        if (a.realName().isEmpty()) {
            return addToAddressBook ? i18n("Add this contact to the address book.") : i18n("Update this contact to the address book.");
        } else {
            return addToAddressBook ? i18n("Add \"%1\" to the address book.", a.realName()) : i18n("Update \"%1\" to the address book.", a.realName());
        }
    }

    bool openVCard(const KContacts::Addressee &a, const QString &vCard) const
    {
        Q_UNUSED(vCard);
        Akonadi::ContactViewer *view = new Akonadi::ContactViewer(nullptr);
        view->setRawContact(a);
        view->setMinimumSize(300, 400);
        view->show();
        return true;
    }

    bool saveAsVCard(const KContacts::Addressee &a, const QString &vCard) const
    {
        QString fileName;
        const QString givenName(a.givenName());
        if (givenName.isEmpty()) {
            fileName = a.familyName() + QStringLiteral(".vcf");
        } else {
            fileName = givenName + QLatin1Char('_') + a.familyName() + QStringLiteral(".vcf");
        }
        // get the saveas file name
        QUrl saveAsUrl
            = QFileDialog::getSaveFileUrl(nullptr, i18n("Save Business Card"), QUrl::fromUserInput(fileName));
        if (saveAsUrl.isEmpty()) {
            return false;
        }

        // put the attachment in a temporary file and save it
        QTemporaryFile tmpFile;
        tmpFile.open();

        QByteArray data = vCard.toUtf8();
        tmpFile.write(data);
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), saveAsUrl, -1, KIO::Overwrite);
        return job->exec();
    }
};

class Plugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "text_vcard.json")
public:
    const MimeTreeParser::Interface::BodyPartFormatter *bodyPartFormatter(int idx) const override
    {
        return validIndex(idx) ? new Formatter() : nullptr;
    }

    const MimeTreeParser::Interface::BodyPartURLHandler *urlHandler(int idx) const override
    {
        return validIndex(idx) ? new UrlHandler() : nullptr;
    }

private:
    bool validIndex(int idx) const
    {
        return idx == 0;
    }
};
}

#include "text_vcard.moc"
