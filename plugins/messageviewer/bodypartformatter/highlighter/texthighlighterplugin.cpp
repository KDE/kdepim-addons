/*
    This file is part of kdepim.

    Copyright (c) 2004 Till Adam <adam@kde.org>

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

#include "highlighter.h"

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/HtmlWriter>

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>

#include <grantlee/template.h>

#include <QGuiApplication>
#include <QMimeDatabase>
#include <QMimeType>
#include <QPalette>

namespace {
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || mp->isHidden() || mp->text().isEmpty() || mp->asIcon() != MimeTreeParser::NoIcon) {
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
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([=](Grantlee::OutputStream *) {
                Highlighter highLighter(htmlWriter->stream());
                highLighter.setDefinition(def);
                highLighter.setTheme(QGuiApplication::palette().color(QPalette::Base).lightness() < 128
                                     ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                     : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
                highLighter.highlight(msgPart->text());
            }));

        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/textmessagepart.html"));
        Grantlee::OutputStream s(htmlWriter->stream());
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
