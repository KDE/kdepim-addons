/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MimeTreeParser/MessagePart>
#include <MessageViewer/HtmlWriter>


#include <grantlee/template.h>
#include <QTextDocument>
#include <QGuiApplication>
#include <QMimeDatabase>
#include <QDebug>

namespace {
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
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
            QTextDocument textDocument;
            textDocument.setMarkdown(msgPart->text());
            const QString result = textDocument.toHtml();
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
