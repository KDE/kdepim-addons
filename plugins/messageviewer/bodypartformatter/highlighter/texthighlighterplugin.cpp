/*
    This file is part of kdepim.

    SPDX-FileCopyrightText: 2004 Till Adam <adam@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "highlighter.h"

#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>

#include <KTextTemplate/Template>

#include <QGuiApplication>
#include <QMimeDatabase>
#include <QPalette>
using namespace Qt::Literals::StringLiterals;

namespace
{
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || context->isHiddenHint(msgPart) || mp->text().isEmpty() || context->displayHint(msgPart) != MimeTreeParser::NoIcon) {
            return false;
        }

        QMimeDatabase db;
        auto mt = db.mimeTypeForName(QString::fromLatin1(msgPart->content()->contentType()->mimeType().toLower()));
        if (!mt.isValid()) {
            return false;
        }
        if (mt.name() != QLatin1StringView("text/plain") && !mt.allAncestors().contains(QLatin1StringView("text/plain"))) {
            return false;
        }

        const auto def = mRepo.definitionForFileName(mp->label());
        if (!def.isValid()) {
            return false;
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(u"block"_s, msgPart.data());
        c.insert(u"showOnlyOneMimePart"_s, context->showOnlyOneMimePart());
        c.insert(u"content"_s, QVariant::fromValue<MessageViewer::KTextTemplateCallback>([this, htmlWriter, def, msgPart](KTextTemplate::OutputStream *) {
                     Highlighter highLighter(htmlWriter->stream());
                     highLighter.setDefinition(def);
                     highLighter.setTheme(QGuiApplication::palette().color(QPalette::Base).lightness() < 128
                                              ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                              : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
                     highLighter.highlight(msgPart->text());
                 }));

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(u"textmessagepart.html"_s);
        KTextTemplate::OutputStream s(htmlWriter->stream());
        t->render(&s, &c);
        return true;
    }

private:
    mutable KSyntaxHighlighting::Repository mRepo;
};

class Plugin : public QObject, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "texthighlighterplugin.json")
public:
    [[nodiscard]] std::unique_ptr<MessageViewer::MessagePartRendererBase> renderer(int index) override
    {
        if (index == 0) {
            return std::make_unique<Formatter>();
        }
        return nullptr;
    }
};
}

#include "texthighlighterplugin.moc"
