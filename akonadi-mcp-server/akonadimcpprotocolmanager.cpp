/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadimcpprotocolmanager.h"
#include "akonadiresourcesstatus/akonadiresourcesstatustool.h"
#include "calendareventstool/calendareventstool.h"
#include "contactgroupexpandtool/contactgroupexpandtool.h"
#include "contactsearchtool/contactsearchtool.h"
#include "createcontacttool/createcontacttool.h"
#include "createeventtool/createeventtool.h"
#include "createjournaltool/createjournaltool.h"
#include "createmailtool/createmailtool.h"
#include "createtodotool/createtodotool.h"
#include "editmailtool/editmailtool.h"
#include "freebusytool/freebusytool.h"
#include "listaddressbooks/listaddressbookstool.h"
#include "listcalendars/listcalendarstool.h"
#include "listidentities/listidentitiestool.h"
#include "mailsearch/searchmailtool.h"
#include "markmailtool/markmailtool.h"
#include "openmailtool/openmailtool.h"
#include "replymailtool/replymailtool.h"
#include "todolisttool/todolisttool.h"
#include "upcomingbirthdaystool/upcomingbirthdaystool.h"
#include "updatecontacttool/updatecontacttool.h"
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
    addTool(std::make_unique<UpcomingBirthdaysTool>());
    addTool(std::make_unique<CalendarEventsTool>());
    addTool(std::make_unique<FreeBusyTool>());
    addTool(std::make_unique<TodoListTool>());
    addTool(std::make_unique<AkonadiResourcesStatusTool>());
    addTool(std::make_unique<CreateContactTool>());
    addTool(std::make_unique<SearchMailTool>());
    addTool(std::make_unique<CreateMailTool>());
    addTool(std::make_unique<OpenMailTool>());
    addTool(std::make_unique<ReplyMailTool>());
    addTool(std::make_unique<EditMailTool>());
    addTool(std::make_unique<CreateEventTool>());
    addTool(std::make_unique<CreateTodoTool>());
    addTool(std::make_unique<CreateJournalTool>());
    addTool(std::make_unique<ListCalendarsTool>());
    addTool(std::make_unique<ListIdentitiesTool>());
    addTool(std::make_unique<MarkMailTool>());
    addTool(std::make_unique<UpdateContactTool>());
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
