/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>

#include "markdownabstract.h"
#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>
#ifdef USE_DISCOUNT_LIB
#include "markdowndiscount.h"
#else
#include "markdownqtextdocument.h"
#endif

#include <KTextTemplate/Template>
#include <QMimeDatabase>
#include <QTextDocument>

namespace
{
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context)
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || context->isHiddenHint(msgPart) || mp->text().isEmpty() || context->displayHint(msgPart) != MimeTreeParser::NoIcon) {
            return false;
        }

        QMimeDatabase db;
        auto mt = db.mimeTypeForName(QString::fromLatin1(msgPart->content()->contentType()->mimeType().toLower()));
        if (!mt.isValid()) {
            return false;
        }
        if (mt.name() != QLatin1String("text/markdown") && !mt.allAncestors().contains(QLatin1String("text/markdown"))) {
            return false;
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("showOnlyOneMimePart"), context->showOnlyOneMimePart());
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::KTextTemplateCallback>([=](KTextTemplate::OutputStream *) {
                     QString result;
#ifdef USE_DISCOUNT_LIB
                     MarkdownDiscount engine;
                     engine.setText(msgPart->text());
                     result = engine.toHtml();
#else
                     MarkdownQTextDocument engine;
                     engine.setText(msgPart->text());
                     result = engine.toHtml();
#endif
                     (*htmlWriter->stream()) << result;
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
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "textmarkdownplugin.json")
public:
    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        if (index == 0) {
            return new Formatter();
        }
        return nullptr;
    }
};
}

#include "textmarkdownplugin.moc"
