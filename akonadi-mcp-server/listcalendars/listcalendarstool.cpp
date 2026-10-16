/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "listcalendarstool.h"
#include "listcalendarstooljob.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
ListCalendarsTool::ListCalendarsTool() = default;
ListCalendarsTool::~ListCalendarsTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ListCalendarsTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"list_calendars"_s, u"List the Akonadi calendars"_s);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("List Calendars"));
    tool.setAnnotations(annotation);
    return tool;
}

void ListCalendarsTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    auto job = new ListCalendarsToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->start();
}
