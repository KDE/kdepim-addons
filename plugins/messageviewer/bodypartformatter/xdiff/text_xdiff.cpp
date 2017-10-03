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

#include "diffhighlighter.h"

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/HtmlWriter>

#include <grantlee/template.h>

namespace {
// FIXME: The box should only be as wide as necessary.

class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || mp->isHidden() || mp->text().isEmpty() || mp->asIcon() != MimeTreeParser::NoIcon)
            return false;

        const bool diffMimeType = msgPart->content()->contentType()->mimeType() == "text/x-patch"
                               || msgPart->content()->contentType()->mimeType() == "text/x-diff";
        const bool diffFileName = msgPart->content()->contentType()->name().endsWith(QLatin1String(".diff"))
                               || msgPart->content()->contentType()->name().endsWith(QLatin1String(".patch"));
        if (!diffMimeType && !diffFileName)
            return false;

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), msgPart.data());
        c.insert(QStringLiteral("content"), QVariant::fromValue<MessageViewer::GrantleeCallback>([msgPart](Grantlee::OutputStream *stream) {
            DiffHighlighter highLighter;
            highLighter.highlightDiff(msgPart->text());
            *stream << highLighter.outputDiff();
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
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "text_xdiff.json")
public:
    MessageViewer::MessagePartRendererBase* renderer(int index) override
    {
        if (index == 0)
            return new Formatter();
        return nullptr;
    }
};
}

#include "text_xdiff.moc"
