/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtool.h"
#include "common/toolutils.h"
#include "markmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

MarkMailTool::MarkMailTool() = default;
MarkMailTool::~MarkMailTool() = default;

namespace
{
// Returns false when the value is present but isn't a boolean
[[nodiscard]] bool readOptionalBool(const QMap<QString, QJsonValue> &args, const QString &key, std::optional<bool> &result)
{
    const QJsonValue value = args.value(key);
    if (value.isUndefined() || value.isNull()) {
        return true;
    }
    if (!value.isBool()) {
        return false;
    }
    result = value.toBool();
    return true;
}
}

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
    tool.setTitle(i18n("Mark Mail"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
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

    std::optional<bool> readValue;
    if (!readOptionalBool(call->arguments(), u"read"_s, readValue)) {
        call->finishWithText(i18n("Argument read must be a boolean"), true);
        return;
    }

    std::optional<bool> important;
    if (!readOptionalBool(call->arguments(), u"important"_s, important)) {
        call->finishWithText(i18n("Argument important must be a boolean"), true);
        return;
    }
    if (!readValue && !important) {
        call->finishWithText(i18n("At least one of read or important must be given"), true);
        return;
    }

    auto job = new MarkMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setRead(readValue);
    job->setImportant(important);
    job->start();
}
