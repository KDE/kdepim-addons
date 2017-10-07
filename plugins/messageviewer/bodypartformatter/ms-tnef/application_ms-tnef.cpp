/*
    Copyright (c) 2010 Volker Krause <vkrause@kde.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful, but
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

#include "ms_tnef_debug.h"

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessageViewerUtil>
#include <MessageViewer/MimeType>

#include <MessageCore/StringUtil>

#include <MimeTreeParser/HtmlWriter>
#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/NodeHelper>

#include <KCalCore/Event>
#include <KCalCore/Incidence>
#include <KCalCore/ICalFormat>
#include <KCalCore/MemoryCalendar>

#include <KCalUtils/IncidenceFormatter>

#include <ktnef/formatter.h>
#include <ktnef/ktnefparser.h>
#include <ktnef/ktnefmessage.h>
#include <ktnef/ktnefattach.h>

#include <grantlee/template.h>

#include <KIconLoader>
#include <KLocalizedString>

#include <QDir>
#include <QFile>

namespace {
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || mp->isHidden()) {
            return false;
        }

        if (mp->content()->contentType()->mimeType() != QByteArrayLiteral("application/vnd.ms-tnef") &&
            mp->content()->contentType()->mimeType() != QByteArrayLiteral("application/ms-tnef")) {
            return false;
        }

        const auto fileName = mp->temporaryFilePath();
        KTnef::KTNEFParser parser;
        if (!parser.openFile(fileName) || !parser.message()) {
            qCDebug(MS_TNEF_LOG) << "Could not parse" << fileName;
            return false;
        }

        // Look for an invitation
        QString inviteStr;
        QFile f(fileName);
        QByteArray buf;
        if (!f.open(QIODevice::ReadOnly)) {
            qCWarning(MS_TNEF_LOG) << "Failed to read attachment part: " << f.errorString();
        } else {
            buf = f.readAll();
            f.close();
        }
        if (!buf.isEmpty()) {
            KCalCore::MemoryCalendar::Ptr cl(
                new KCalCore::MemoryCalendar(QTimeZone::systemTimeZone()));
            KCalUtils::InvitationFormatterHelper helper;
            const QString invite = KTnef::formatTNEFInvitation(buf, cl, &helper);
            KCalCore::ICalFormat format;
            KCalCore::Incidence::Ptr inc = format.fromString(invite);
            KCalCore::Event::Ptr event = inc.dynamicCast<KCalCore::Event>();
            if (event && event->hasEndDate()) {
                // no enddate => not a valid invitation
                inviteStr = KCalUtils::IncidenceFormatter::extensiveDisplayStr(cl, inc);
            }
        }

        mp->setShowTextFrame(true);
        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([&](Grantlee::OutputStream *stream) {
            const auto tnefatts = parser.message()->attachmentList();
            if (tnefatts.isEmpty() && inviteStr.isEmpty()) {
                qCDebug(MS_TNEF_LOG) << "No attachments or invitation found in" << fileName;
                (*stream) << QStringLiteral("&nbsp;&lt;") << i18nc("TNEF attachment has no content", "empty") << QStringLiteral("&gt;");
                return;
            }

            if (!inviteStr.isEmpty()) {
                (*stream) <<  inviteStr;
            }

            const int numberOfTnef(tnefatts.count());
            for (int i = 0; i < numberOfTnef; ++i) {
                KTnef::KTNEFAttach *att = tnefatts.at(i);
                QString label = att->displayName();
                if (label.isEmpty()) {
                    label = att->name();
                }
                label = MessageCore::StringUtil::quoteHtmlChars(label, true);

                const QString dir = mp->nodeHelper()->createTempDir(QStringLiteral("ktnef-") + QString::number(i));
                parser.extractFileTo(att->name(), dir);

                // falling back to internal TNEF attachement name if no filename is given for the attached file
                // this follows the logic of KTNEFParser::extractFileTo(...)
                QString attFileName = att->fileName();
                if (attFileName.isEmpty()) {
                    attFileName = att->name();
                }
                mp->nodeHelper()->addTempFile(dir + QDir::separator() + attFileName);
                const QString href = QStringLiteral("file:") + dir + QDir::separator() + attFileName;

                const QString iconName = QUrl::fromLocalFile(MessageViewer::Util::iconPathForMimetype(att->mimeTag(),
                                                                                                    KIconLoader::Desktop, attFileName)).url();

                (*stream) << QStringLiteral("<div><a href=\"") << href << QStringLiteral("\"><img src=\"")
                          << iconName << QStringLiteral("\" border=\"0\" style=\"max-width: 100%\"/>") << label
                          << QStringLiteral("</a></div><br/>");
            }
        }));

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/textmessagepart.html"));
        Grantlee::OutputStream s(htmlWriter->stream());
        t->render(&s, &c);
        return true;
    }
};

class Plugin : public QObject, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "application_ms-tnef.json")
public:
    MessageViewer::MessagePartRendererBase* renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "application_ms-tnef.moc"
