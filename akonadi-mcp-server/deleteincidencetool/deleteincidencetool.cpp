/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deleteincidencetool.h"
#include "common/toolutils.h"
#include "deleteincidencetooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

DeleteIncidenceTool::DeleteIncidenceTool() = default;
DeleteIncidenceTool::~DeleteIncidenceTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool DeleteIncidenceTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_delete_incidence"_s,
        u"Delete an event, to-do or journal entry from an Akonadi calendar. For a recurring incidence, all occurrences are deleted. This cannot be undone"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the incidence item (see calendar_events and calendar_todo_list)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(true);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Delete Incidence"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Calendar);
    return tool;
}

void DeleteIncidenceTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QJsonValue idValue = call->arguments().value(u"id"_s);
    if (!idValue.isDouble()) {
        call->finishWithText(i18n("Argument id must be an integer"), true);
        return;
    }
    const qint64 itemId = idValue.toInteger(-1);
    if (itemId < 0) {
        call->finishWithText(i18n("Argument id must be a positive integer"), true);
        return;
    }

    auto job = new DeleteIncidenceToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->start();
}
