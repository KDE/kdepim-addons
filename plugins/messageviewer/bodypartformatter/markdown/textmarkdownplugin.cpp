/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MimeTreeParser/MessagePart>
#include <MessageViewer/HtmlWriter>
#include "markdownabstract.h"
#ifdef USE_DISCOUNT_LIB
#include "markdowndiscount.h"
#else
#include "markdownqtextdocument.h"
#endif

#include <grantlee/template.h>
#include <QTextDocument>
#include <QMimeDatabase>

namespace {
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
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([=](Grantlee::OutputStream *) {
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
        Grantlee::OutputStream s(htmlWriter->stream());
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
