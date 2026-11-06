/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "listcalendarstool.h"
#include "common/toolutils.h"
#include "listcalendarstooljob.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
ListCalendarsTool::ListCalendarsTool() = default;
ListCalendarsTool::~ListCalendarsTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ListCalendarsTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"calendar_list"_s,
                                                                               i18n("List Calendars"),
                                                                               u"List the Akonadi calendars"_s,
                                                                               TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::ReadOnly);
    ToolUtils::addToolMeta(tool, ToolUtils::Calendar);
    return tool;
}

void ListCalendarsTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    auto job = new ListCalendarsToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->start();
}
