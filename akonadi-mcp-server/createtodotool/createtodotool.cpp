/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createtodotool.h"
#include "calendarcommon/calendartoolutils.h"
#include "calendarcommon/createincidencetooljob.h"
#include <KCalendarCore/Todo>
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int highestPriority = 1;
constexpr int lowestPriority = 9;
}
CreateTodoTool::CreateTodoTool() = default;
CreateTodoTool::~CreateTodoTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateTodoTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_create_todo"_s,
        u"Create a new to-do (task) in an Akonadi calendar"_s,
        QMap<QString, QJsonObject>{
            {u"summary"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Title of the to-do"_s)},
            {u"due"_s,
             McpProtocolServerTool::schemaProperty(u"string"_s,
                                                   u"Due date, as ISO 8601 date (2026-10-14) or local date-time (2026-10-14T14:00). Default: no due date"_s)},
            {u"priority"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Priority from 1 (highest) to 9 (lowest). Default: undefined"_s)},
            {u"description"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Description of the to-do"_s)},
            {u"calendar_id"_s,
             McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                   u"Identifier of the calendar (see calendar_list). If omitted, the first writable calendar is used"_s)}},
        {u"summary"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Create To-do"));
    tool.setAnnotations(annotation);
    return tool;
}

void CreateTodoTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString summary = arguments.value(u"summary"_s).toString().trimmed();
    if (summary.isEmpty()) {
        call->finishWithText(i18n("Argument summary must be a non-empty string"), true);
        return;
    }

    const auto todo = KCalendarCore::Todo::Ptr::create();
    todo->setSummary(summary);

    if (const QJsonValue dueValue = arguments.value(u"due"_s); !dueValue.isUndefined() && !dueValue.isNull()) {
        const std::optional<CalendarToolUtils::IncidenceDateTime> due = CalendarToolUtils::parseIncidenceDateTime(dueValue.toString());
        if (!due) {
            call->finishWithText(i18n("Argument due must be an ISO 8601 date or date-time"), true);
            return;
        }
        todo->setDtDue(due->dateTime);
        todo->setAllDay(due->allDay);
    }

    const QJsonValue priorityValue = arguments.value(u"priority"_s);
    if (priorityValue.isDouble()) {
        const int priority = priorityValue.toInt(-1);
        if (priority < highestPriority || priority > lowestPriority) {
            call->finishWithText(i18n("Argument priority must be an integer between %1 and %2", highestPriority, lowestPriority), true);
            return;
        }
        todo->setPriority(priority);
    } else if (!priorityValue.isUndefined() && !priorityValue.isNull()) {
        call->finishWithText(i18n("Argument priority must be an integer"), true);
        return;
    }

    if (const QString description = arguments.value(u"description"_s).toString().trimmed(); !description.isEmpty()) {
        todo->setDescription(description);
    }

    Akonadi::Collection::Id calendarId = -1;
    const QJsonValue calendarValue = arguments.value(u"calendar_id"_s);
    if (calendarValue.isDouble()) {
        calendarId = calendarValue.toInteger(-1);
        if (calendarId < 0) {
            call->finishWithText(i18n("Argument calendar_id must be a positive integer"), true);
            return;
        }
    } else if (!calendarValue.isUndefined() && !calendarValue.isNull()) {
        call->finishWithText(i18n("Argument calendar_id must be an integer"), true);
        return;
    }

    auto job = new CreateIncidenceToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setIncidence(todo);
    job->setCalendarId(calendarId);
    job->start();
}
