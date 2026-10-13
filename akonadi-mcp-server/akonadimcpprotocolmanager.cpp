/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadimcpprotocolmanager.h"
#include "contactgroupexpandtool/contactgroupexpandtool.h"
#include "contactsearchtool/contactsearchtool.h"
#include "listaddressbooks/listaddressbookstool.h"
#include <KLocalizedString>
#include <QUrl>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
namespace
{
constexpr int toolsPageSize = 2;
}
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
    setInstructions(i18n("Manage information from Akonadi"));
    setToolsPageSize(toolsPageSize);

    addTool(std::make_unique<ContactSearchTool>());
    addTool(std::make_unique<ContactGroupExpandTool>());
    addTool(std::make_unique<ListAddressBooksTool>());
    // TODO add more
}

AkonadiMcpProtocolManager::~AkonadiMcpProtocolManager() = default;

void AkonadiMcpProtocolManager::start(const QString &url)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(url));
    setSettings(settings);
    McpProtocolServerProtocolManager::start();
}
#include "moc_akonadimcpprotocolmanager.cpp"
