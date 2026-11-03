/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updateincidencetool.h"
#include "common/toolutils.h"
#include "updateincidencetooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

namespace
{
constexpr int undefinedPriority = 0;
constexpr int lowestPriority = 9;
}

UpdateIncidenceTool::UpdateIncidenceTool() = default;
UpdateIncidenceTool::~UpdateIncidenceTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool UpdateIncidenceTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_update_incidence"_s,
        i18n("Update Incidence"),
        u"Update an existing event, to-do or journal entry in an Akonadi calendar. Only the provided fields are modified"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::Destructive,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the incidence item (see calendar_events and calendar_todo_list)"_s)},
            {u"summary"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Title of the incidence"_s)},
            {u"description"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Description of the incidence, an empty string clears it"_s)},
            {u"location"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Location of the incidence, an empty string clears it"_s)},
            {u"start"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Start of the event or to-do, or date of the journal entry, as ISO 8601 date (2026-10-14) for all day or local date-time "
                 u"(2026-10-14T14:00). When only the start of an event is changed, its duration is kept"_s)},
            {u"end"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Events only: end of the event, same format as start. For an all-day event, the date is the last day of the event"_s)},
            {u"due"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"To-dos only: due date, same format as start, an empty string removes it"_s)},
            {u"priority"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"To-dos only: priority from 1 (highest) to 9 (lowest), 0 for undefined"_s)},
            {u"completed"_s, McpProtocolServerTool::schemaProperty(u"boolean"_s, u"To-dos only: mark the to-do as completed or not completed"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation = tool.annotations().value();
    annotation.setIdempotentHint(true);
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Calendar);
    return tool;
}

void UpdateIncidenceTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QJsonValue idValue = arguments.value(u"id"_s);
    const std::optional<qint64> itemIdArgument = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(idValue);
    if (!itemIdArgument) {
        call->finishWithText(i18n("Argument id must be an integer"), true);
        return;
    }
    const qint64 itemId = *itemIdArgument;
    if (itemId < 0) {
        call->finishWithText(i18n("Argument id must be a positive integer"), true);
        return;
    }

    UpdateIncidenceToolJob::IncidenceChanges changes;

    if (const QJsonValue summaryValue = arguments.value(u"summary"_s);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(summaryValue)) {
        const QString summary = summaryValue.toString().trimmed();
        if (!summaryValue.isString() || summary.isEmpty()) {
            call->finishWithText(i18n("Argument summary must be a non-empty string"), true);
            return;
        }
        changes.summary = summary;
    }

    if (!TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::readOptionalString(arguments, u"description"_s, changes.description)) {
        call->finishWithText(i18n("Argument description must be a string"), true);
        return;
    }

    if (!TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::readOptionalString(arguments, u"location"_s, changes.location)) {
        call->finishWithText(i18n("Argument location must be a string"), true);
        return;
    }

    if (const QJsonValue startValue = arguments.value(u"start"_s);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(startValue)) {
        changes.start = CalendarToolUtils::parseIncidenceDateTime(startValue.toString());
        if (!startValue.isString() || !changes.start) {
            call->finishWithText(i18n("Argument start must be an ISO 8601 date or date-time"), true);
            return;
        }
    }

    if (const QJsonValue endValue = arguments.value(u"end"_s); TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(endValue)) {
        changes.end = CalendarToolUtils::parseIncidenceDateTime(endValue.toString());
        if (!endValue.isString() || !changes.end) {
            call->finishWithText(i18n("Argument end must be an ISO 8601 date or date-time"), true);
            return;
        }
        if (changes.start && changes.start->allDay != changes.end->allDay) {
            call->finishWithText(i18n("Arguments start and end must both be dates or both be date-times"), true);
            return;
        }
    }

    std::optional<QString> dueStr;
    if (!TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::readOptionalString(arguments, u"due"_s, dueStr)) {
        call->finishWithText(i18n("Argument due must be a string"), true);
        return;
    }
    if (dueStr) {
        // An empty string removes the due date
        if (dueStr->isEmpty()) {
            changes.due = CalendarToolUtils::IncidenceDateTime{};
        } else {
            changes.due = CalendarToolUtils::parseIncidenceDateTime(*dueStr);
            if (!changes.due) {
                call->finishWithText(i18n("Argument due must be an ISO 8601 date or date-time"), true);
                return;
            }
            if (changes.start && changes.start->allDay != changes.due->allDay) {
                call->finishWithText(i18n("Arguments start and due must both be dates or both be date-times"), true);
                return;
            }
        }
    }

    if (const QJsonValue priorityValue = arguments.value(u"priority"_s);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(priorityValue)) {
        const std::optional<qint64> priority = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(priorityValue);
        if (!priority || *priority < undefinedPriority || *priority > lowestPriority) {
            call->finishWithText(i18n("Argument priority must be an integer between %1 and %2", undefinedPriority, lowestPriority), true);
            return;
        }
        changes.priority = static_cast<int>(*priority);
    }

    if (const QJsonValue completedValue = arguments.value(u"completed"_s);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(completedValue)) {
        const std::optional<bool> completed = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::boolean(completedValue);
        if (!completed) {
            call->finishWithText(i18n("Argument completed must be a boolean"), true);
            return;
        }
        changes.completed = *completed;
    }

    if (changes.isEmpty()) {
        call->finishWithText(i18n("No field to update"), true);
        return;
    }

    auto job = new UpdateIncidenceToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setChanges(changes);
    job->start();
}
