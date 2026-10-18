/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtool.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

MarkMailTool::MarkMailTool() = default;
MarkMailTool::~MarkMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool MarkMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_mark"_s,
        u"Mark a mail as read or unread, important or not important"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search)"_s)},
            {u"read"_s, McpProtocolServerTool::schemaProperty(u"boolean"_s, u"Mark the mail as read (true) or unread (false)"_s)},
            {u"important"_s, McpProtocolServerTool::schemaProperty(u"boolean"_s, u"Mark the mail as important (true) or not important (false)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Mark Mail"));
    tool.setAnnotations(annotation);
    return tool;
}

void MarkMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    const QJsonValue readValue = call->arguments().value(u"read"_s);
    if (!readValue.isUndefined() && !readValue.isBool()) {
        call->finishWithText(i18n("Argument read must be a boolean"), true);
        return;
    }

    const QJsonValue importantValue = call->arguments().value(u"important"_s);
    if (!importantValue.isUndefined() && !importantValue.isBool()) {
        call->finishWithText(i18n("Argument important must be a boolean"), true);
        return;
    }

    // TODO implement it
    call->finishWithText(i18n("Not implemented yet"), true);
}
