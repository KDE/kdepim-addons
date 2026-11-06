/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "movemailtool.h"
#include "common/toolutils.h"
#include "movemailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

MoveMailTool::MoveMailTool() = default;
MoveMailTool::~MoveMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool MoveMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_move"_s,
        i18n("Move Mail"),
        u"Move a mail to another Akonadi mail folder. The destination is given either by folder or by folder_id"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::Modify,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search)"_s)},
            {u"folder"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Name of the destination folder (Archives) or its path from the account, separated by '/' (Local Folders/Archives). Case insensitive"_s)},
            {u"folder_id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the destination folder (see mail_search)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation = tool.annotations().value();
    annotation.setIdempotentHint(true);
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void MoveMailTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    std::optional<QString> folder;
    if (!TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::readOptionalString(arguments, u"folder"_s, folder)) {
        call->finishWithText(i18n("Argument folder must be a string"), true);
        return;
    }
    if (folder && folder->isEmpty()) {
        call->finishWithText(i18n("Argument folder must not be empty"), true);
        return;
    }

    qint64 folderId = -1;
    if (const QJsonValue folderIdValue = arguments.value(u"folder_id"_s);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(folderIdValue)) {
        const std::optional<qint64> id = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(folderIdValue);
        if (!id || *id < 0) {
            call->finishWithText(i18n("Argument folder_id must be a positive integer"), true);
            return;
        }
        folderId = *id;
    }

    if (folder.has_value() == (folderId >= 0)) {
        call->finishWithText(i18n("Exactly one of folder or folder_id must be given"), true);
        return;
    }

    auto job = new MoveMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setFolderId(folderId);
    job->setFolder(folder.value_or(QString()));
    job->start();
}
