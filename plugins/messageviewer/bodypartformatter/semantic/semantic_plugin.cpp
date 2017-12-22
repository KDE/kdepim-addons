/*
   Copyright (c) 2017 Volker Krause <vkrause@kde.org>

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by
   the Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
   License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "semanticprocessor.h"
#include "semanticrenderer.h"
#include "semanticurlhandler.h"

#include <MessageViewer/MessagePartRenderPlugin>
#include <MimeTreeParser/BodyPartFormatter>

// needs to be outside of the anonymous namespace
static void initResource()
{
    Q_INIT_RESOURCE(extractors);
}

namespace {
class SemanticPlugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "semantic_plugin.json")
public:
    SemanticPlugin()
    {
        initResource();
    }

    const MimeTreeParser::Interface::BodyPartFormatter *bodyPartFormatter(int idx) const override
    {
        if (idx < 3) {
            return new SemanticProcessor();
        }
        return nullptr;
    }

    MessageViewer::MessagePartRendererBase *renderer(int idx) override
    {
        if (idx == 0) {
            return new SemanticRenderer();
        }
        return nullptr;
    }

    const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override
    {
        if (idx == 0) {
            return new SemanticUrlHandler();
        }
        return nullptr;
    }
};
}

#include "semantic_plugin.moc"
