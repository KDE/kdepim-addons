/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itinerarykdeconnecthandler.h"
#include "itineraryprocessor.h"
#include "itineraryrenderer.h"
#include "itineraryurlhandler.h"

#include <MessageViewer/MessagePartRenderPlugin>
#include <MimeTreeParser/BodyPartFormatter>

namespace
{
class ItineraryPlugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "itinerary_plugin.json")
public:
    explicit ItineraryPlugin(QObject *parent = nullptr)
        : QObject(parent)
        , m_kdeConnect(new ItineraryKDEConnectHandler(this))
    {
    }

    [[nodiscard]] const MimeTreeParser::Interface::BodyPartFormatter *bodyPartFormatter(int idx) const override
    {
        if (idx < 3) {
            return new ItineraryProcessor();
        }
        return nullptr;
    }

    MessageViewer::MessagePartRendererBase *renderer(int idx) override
    {
        if (idx == 0) {
            auto renderer = new ItineraryRenderer();
            renderer->setKDEConnectHandler(m_kdeConnect);
            return renderer;
        }
        return nullptr;
    }

    [[nodiscard]] const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override
    {
        if (idx == 0) {
            auto handler = new ItineraryUrlHandler();
            handler->setKDEConnectHandler(m_kdeConnect);
            return handler;
        }
        return nullptr;
    }

private:
    ItineraryKDEConnectHandler *const m_kdeConnect;
};
}

#include "itinerary_plugin.moc"
