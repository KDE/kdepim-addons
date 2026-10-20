/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "movemailtool.h"
#include "common/toolutils.h"
#include "movemailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

MoveMailTool::MoveMailTool() = default;
MoveMailTool::~MoveMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool MoveMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_move"_s,
        u"Move a mail to another Akonadi mail folder. The destination is given either by folder or by folder_id"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search)"_s)},
            {u"folder"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Name of the destination folder (Archives) or its path from the account, separated by '/' (Local Folders/Archives). Case insensitive"_s)},
            {u"folder_id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the destination folder (see mail_search)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Move Mail"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void MoveMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QJsonValue idValue = arguments.value(u"id"_s);
    if (!idValue.isDouble()) {
        call->finishWithText(i18n("Argument id must be an integer"), true);
        return;
    }
    const qint64 itemId = idValue.toInteger(-1);
    if (itemId < 0) {
        call->finishWithText(i18n("Argument id must be a positive integer"), true);
        return;
    }

    std::optional<QString> folder;
    if (!ToolUtils::readOptionalString(arguments, u"folder"_s, folder)) {
        call->finishWithText(i18n("Argument folder must be a string"), true);
        return;
    }
    if (folder && folder->isEmpty()) {
        call->finishWithText(i18n("Argument folder must not be empty"), true);
        return;
    }

    qint64 folderId = -1;
    if (const QJsonValue folderIdValue = arguments.value(u"folder_id"_s); ToolUtils::isProvided(folderIdValue)) {
        if (!folderIdValue.isDouble() || folderIdValue.toInteger(-1) < 0) {
            call->finishWithText(i18n("Argument folder_id must be a positive integer"), true);
            return;
        }
        folderId = folderIdValue.toInteger();
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
