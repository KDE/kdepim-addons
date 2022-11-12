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

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/template.h>
#else
#include <KTextTemplate/Template>
#endif

#include <QGuiApplication>
#include <QMimeDatabase>
#include <QPalette>

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
        if (mt.name() != QLatin1String("text/plain") && !mt.allAncestors().contains(QLatin1String("text/plain"))) {
            return false;
        }

        const auto def = mRepo.definitionForFileName(mp->label());
        if (!def.isValid()) {
            return false;
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("showOnlyOneMimePart"), context->showOnlyOneMimePart());
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([=](Grantlee::OutputStream *) {
                     Highlighter highLighter(htmlWriter->stream());
                     highLighter.setDefinition(def);
                     highLighter.setTheme(QGuiApplication::palette().color(QPalette::Base).lightness() < 128
                                              ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                              : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
                     highLighter.highlight(msgPart->text());
                 }));
#else
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([=](KTextTemplate::OutputStream *) {
                     Highlighter highLighter(htmlWriter->stream());
                     highLighter.setDefinition(def);
                     highLighter.setTheme(QGuiApplication::palette().color(QPalette::Base).lightness() < 128
                                              ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                              : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
                     highLighter.highlight(msgPart->text());
                 }));
#endif

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("textmessagepart.html"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        Grantlee::OutputStream s(htmlWriter->stream());
#else
        KTextTemplate::OutputStream s(htmlWriter->stream());
#endif
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
    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        if (index == 0) {
            return new Formatter();
        }
        return nullptr;
    }
};
}

#include "texthighlighterplugin.moc"
