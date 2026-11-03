/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "todolisttool.h"
#include "common/toolutils.h"
#include "todolisttooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int maximumDays = 366;
}
TodoListTool::TodoListTool() = default;
TodoListTool::~TodoListTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool TodoListTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_todo_list"_s,
        i18n("To-do List"),
        u"List the to-dos of the Akonadi calendars, sorted by due date and priority"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::ReadOnly,
        QMap<QString, QJsonObject>{
            {u"include_completed"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"boolean"_s, u"Also return the completed to-dos (default false)"_s)},
            {u"due_within_days"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(
                 u"integer"_s,
                 u"Only return the to-dos due in the next days, overdue ones included, from 1 to 366. Default: no limit"_s)}});
    ToolUtils::addToolMeta(tool, ToolUtils::Calendar);
    return tool;
}

void TodoListTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    bool includeCompleted = false;
    const QJsonValue includeCompletedValue = call->arguments().value(u"include_completed"_s);
    if (const std::optional<bool> completed = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::boolean(includeCompletedValue)) {
        includeCompleted = *completed;
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(includeCompletedValue)) {
        call->finishWithText(i18n("Argument include_completed must be a boolean"), true);
        return;
    }

    int dueWithinDays = 0;
    const QJsonValue daysValue = call->arguments().value(u"due_within_days"_s);
    if (const std::optional<qint64> days = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(daysValue)) {
        if (*days < 1 || *days > maximumDays) {
            call->finishWithText(i18n("Argument due_within_days must be an integer between 1 and %1", maximumDays), true);
            return;
        }
        dueWithinDays = static_cast<int>(*days);
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(daysValue)) {
        call->finishWithText(i18n("Argument due_within_days must be an integer"), true);
        return;
    }

    auto job = new TodoListToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setIncludeCompleted(includeCompleted);
    job->setDueWithinDays(dueWithinDays);
    job->start();
}
