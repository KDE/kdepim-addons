/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/MessagePartRendererBase>

class ItineraryKDEConnectHandler;

/** Rendering plugin for itinerary information about the email content. */
class ItineraryRenderer : public MessageViewer::MessagePartRendererBase
{
public:
    ItineraryRenderer();
    void setKDEConnectHandler(ItineraryKDEConnectHandler *kdeConnect);

    [[nodiscard]] bool
    render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override;

private:
    ItineraryKDEConnectHandler *m_kdeConnect = nullptr;
};
