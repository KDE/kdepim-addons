/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deletecontacttool.h"
#include "common/toolutils.h"
#include "deletecontacttooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

DeleteContactTool::DeleteContactTool() = default;
DeleteContactTool::~DeleteContactTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool DeleteContactTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_delete"_s,
        i18n("Delete Contact"),
        u"Delete a contact from an Akonadi address book. This cannot be undone"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::Destructive,
        QMap<QString, QJsonObject>{{u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the contact item (see contact_search)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation = tool.annotations().value();
    annotation.setIdempotentHint(true);
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void DeleteContactTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QJsonValue idValue = call->arguments().value(u"id"_s);
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

    auto job = new DeleteContactToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->start();
}
