/*
    SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ms_tnef_debug.h"

#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MimeType>

#include <MessageCore/StringUtil>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/NodeHelper>

#include <KCalendarCore/Event>
#include <KCalendarCore/ICalFormat>
#include <KCalendarCore/Incidence>
#include <KCalendarCore/MemoryCalendar>

#include <KCalUtils/IncidenceFormatter>

#include <ktnef/formatter.h>
#include <ktnef/ktnefattach.h>
#include <ktnef/ktnefmessage.h>
#include <ktnef/ktnefparser.h>

#include <KTextTemplate/Template>

#include <KIconLoader>
#include <KLocalizedString>

#include <QFile>

namespace
{
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context)
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || context->isHiddenHint(msgPart)) {
            return false;
        }

        const QByteArray mimetype = mp->content()->contentType()->mimeType();
        if (mimetype != QByteArrayLiteral("application/vnd.ms-tnef") && mimetype != QByteArrayLiteral("application/ms-tnef")) {
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
            const KCalendarCore::MemoryCalendar::Ptr cl(new KCalendarCore::MemoryCalendar(QTimeZone::systemTimeZone()));
            KCalUtils::InvitationFormatterHelper helper;
            const QString invite = KTnef::formatTNEFInvitation(buf, cl, &helper);
            KCalendarCore::ICalFormat format;
            const KCalendarCore::Incidence::Ptr inc = format.fromString(invite);
            const KCalendarCore::Event::Ptr event = inc.dynamicCast<KCalendarCore::Event>();
            if (event && event->hasEndDate()) {
                // no enddate => not a valid invitation
                inviteStr = KCalUtils::IncidenceFormatter::extensiveDisplayStr(cl, inc);
            }
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("showOnlyOneMimePart"), context->showOnlyOneMimePart());
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::KTextTemplateCallback>([&](KTextTemplate::OutputStream *stream) {
                     const auto tnefatts = parser.message()->attachmentList();
                     if (tnefatts.isEmpty() && inviteStr.isEmpty()) {
                         qCDebug(MS_TNEF_LOG) << "No attachments or invitation found in" << fileName;
                         (*stream) << QStringLiteral("&nbsp;&lt;") << i18nc("TNEF attachment has no content", "empty") << QStringLiteral("&gt;");
                         return;
                     }

                     if (!inviteStr.isEmpty()) {
                         (*stream) << inviteStr;
                     }

                     const int numberOfTnef(tnefatts.count());
                     for (int i = 0; i < numberOfTnef; ++i) {
                         KTnef::KTNEFAttach *att = tnefatts.at(i);
                         QString label = att->displayName();
                         if (label.isEmpty()) {
                             label = att->name();
                         }
                         label = MessageCore::StringUtil::quoteHtmlChars(label, true);

                         const QString dir = mp->nodeHelper()->createTempDir(QLatin1StringView("ktnef-") + QString::number(i));
                         if (!parser.extractFileTo(att->name(), dir)) {
                             qCDebug(MS_TNEF_LOG) << "No possible to extract file:" << att->name();
                         }

                         // falling back to internal TNEF attachment name if no filename is given for the attached file
                         // this follows the logic of KTNEFParser::extractFileTo(...)
                         QString attFileName = att->fileName();
                         if (attFileName.isEmpty()) {
                             attFileName = att->name();
                         }
                         mp->nodeHelper()->addTempFile(dir + QLatin1Char('/') + attFileName);
                         const QString href = QLatin1StringView("file:") + dir + QLatin1Char('/') + attFileName;

                         const QString iconName =
                             QUrl::fromLocalFile(MessageViewer::Util::iconPathForMimetype(att->mimeTag(), KIconLoader::Desktop, attFileName)).url();

                         (*stream) << QStringLiteral("<div><a href=\"") << href << QStringLiteral("\"><img src=\"") << iconName
                                   << QStringLiteral("\" border=\"0\" style=\"max-width: 100%\"/>") << label << QStringLiteral("</a></div><br/>");
                     }
                 }));

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("textmessagepart.html"));
        KTextTemplate::OutputStream s(htmlWriter->stream());
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
    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "application_ms-tnef.moc"
