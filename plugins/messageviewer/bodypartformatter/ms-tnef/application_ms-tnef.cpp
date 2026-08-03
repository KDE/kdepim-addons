/*
    SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ms_tnef_debug.h"

#include <MessageViewer/HtmlWriter>
#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MimeType>

#include <MessageCore/StringUtil>

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/NodeHelper>

#include <ktnef/formatter.h>
#include <ktnef/ktnefattach.h>
#include <ktnef/ktnefmessage.h>
#include <ktnef/ktnefparser.h>

#include <KTextTemplate/Template>

#include <QBuffer>

namespace
{
class TNEFProcessor : public MimeTreeParser::Interface::BodyPartFormatter
{
public:
    MimeTreeParser::MessagePart::Ptr process(MimeTreeParser::Interface::BodyPart &part) const override
    {
        KMime::Content *node = part.content();
        const auto tnefData = node->decodedBody();
        QBuffer tnefBuffer;
        tnefBuffer.setData(tnefData);

        KTnef::KTNEFParser parser;
        if (!parser.openDevice(&tnefBuffer) || !parser.message()) {
            qCDebug(MS_TNEF_LOG) << "Could not parse TNEF data";
            return {};
        }

        auto t = new MimeTreeParser::TextMessagePart(part.objectTreeParser(), node, false);
        MimeTreeParser::MessagePart::Ptr mp(t);
        mp->setAttachmentContent(node);

        if (const auto rtf = parser.message()->rtfString(); !rtf.isEmpty()) {
            mp->appendSubPart(createSubNode(rtf.toUtf8(), "text/rtf", part));
        }
        if (const auto ical = KTnef::messageToIcal(parser.message()); !ical.isEmpty()) {
            mp->appendSubPart(createSubNode(ical.toUtf8(), "text/calendar", part));
        }
        if (const auto vcard = KTnef::messageToVcard(parser.message()); !vcard.isEmpty()) {
            mp->appendSubPart(createSubNode(vcard, "text/vcard", part));
        }

        const auto attachments = parser.message()->attachmentList();
        for (const auto &attachment : attachments) {
            auto attNode = std::make_unique<KMime::Content>();
            attNode->setBody(QByteArrayView(tnefData).slice(attachment->offset(), attachment->size()).toByteArray());
            attNode->contentType()->setName(attachment->displayName());
            attNode->contentType()->setMimeType(attachment->mimeTag().toUtf8());
            attNode->contentDisposition()->setFilename(attachment->fileName());
            auto attNodePtr = attNode.get();
            part.nodeHelper()->attachExtraContent(node, std::move(attNode));
            mp->appendSubPart(
                MimeTreeParser::AttachmentMessagePart::Ptr(new MimeTreeParser::AttachmentMessagePart(part.objectTreeParser(), attNodePtr, false)));
        }

        return mp->subParts().empty() ? nullptr : mp;
    }

private:
    static MimeTreeParser::MessagePartPtr createSubNode(const QByteArray &data, const char *mimeType, MimeTreeParser::Interface::BodyPart &parent)
    {
        auto node = std::make_unique<KMime::Content>();
        node->setBody(data);
        node->contentType()->setMimeType(mimeType);
        auto nodePtr = node.get();
        parent.nodeHelper()->attachExtraContent(parent.content(), std::move(node));
        return MimeTreeParser::AttachmentMessagePart::Ptr(new MimeTreeParser::AttachmentMessagePart(parent.objectTreeParser(), nodePtr, false));
    }
};

class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        auto mp = msgPart.dynamicCast<MimeTreeParser::TextMessagePart>();
        if (!mp || context->isHiddenHint(msgPart) || !mp->attachmentContent()) {
            return false;
        }

        const QByteArray mimetype = mp->attachmentContent()->contentType()->mimeType();
        if (mimetype != QByteArrayLiteral("application/vnd.ms-tnef") && mimetype != QByteArrayLiteral("application/ms-tnef")) {
            return false;
        }

        // fall back to the default attachment rendering if there's no sub-parts we managed to extract above
        if (std::ranges::none_of(msgPart->subParts(), [](const MimeTreeParser::MessagePart::Ptr &part) {
                return part.dynamicCast<MimeTreeParser::AttachmentMessagePart>() != nullptr;
            })) {
            return false;
        }
        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("showOnlyOneMimePart"), context->showOnlyOneMimePart());
        c.insert(QStringLiteral("content"),
                 QVariant::fromValue<MessageViewer::KTextTemplateCallback>([&]([[maybe_unused]] KTextTemplate::OutputStream *stream) {
                     const auto parts = msgPart->subParts();
                     for (const auto &part : parts) {
                         if (part.dynamicCast<MimeTreeParser::AttachmentMessagePart>()) { // don't render the TNEF data itself
                             context->renderWithFactory(part, htmlWriter);
                         }
                     }
                 }));

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("textmessagepart.html"));
        KTextTemplate::OutputStream s(htmlWriter->stream());
        t->render(&s, &c);
        return true;
    }
};

class Plugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "application_ms-tnef.json")
public:
    [[nodiscard]] const MimeTreeParser::Interface::BodyPartFormatter *bodyPartFormatter(int idx) const override
    {
        return idx < 2 ? new TNEFProcessor() : nullptr;
    }

    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "application_ms-tnef.moc"
