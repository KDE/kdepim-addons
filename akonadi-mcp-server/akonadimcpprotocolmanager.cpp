/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadimcpprotocolmanager.h"

using namespace Qt::Literals::StringLiterals;
AkonadiMcpProtocolManager::AkonadiMcpProtocolManager(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager{
          TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp,
          parent}
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation serverInfo;
    serverInfo.setName(u"akonadi_mcp_protocol"_s);
    serverInfo.setVersion(u"1.0"_s);
    setServerInfo(serverInfo);

    // TODO
}

AkonadiMcpProtocolManager::~AkonadiMcpProtocolManager() = default;
#include "moc_akonadimcpprotocolmanager.cpp"
