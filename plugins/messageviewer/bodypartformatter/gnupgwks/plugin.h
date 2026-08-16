/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/MessagePartRenderPlugin>
#include <MimeTreeParser/BodyPartFormatter>

class ApplicationGnuPGWKSPlugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "gnupgwks.json")
public:
    ApplicationGnuPGWKSPlugin() = default;

    [[nodiscard]] std::unique_ptr<const MimeTreeParser::Interface::BodyPartFormatter> bodyPartFormatter(int idx) const override;
    [[nodiscard]] std::unique_ptr<MessageViewer::MessagePartRendererBase> renderer(int index) override;
    const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override;
};
