/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "forwardmailtool.h"
#include "common/toolutils.h"
#include "forwardmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

namespace
{
const QString inlineMode = u"inline"_s;
const QString attachmentMode = u"attachment"_s;
}

ForwardMailTool::ForwardMailTool() = default;
ForwardMailTool::~ForwardMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ForwardMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_forward"_s,
        i18n("Forward Mail"),
        u"Open a KMail composer to forward a mail, KMail is started if needed. The mail is not sent"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::ReadOnly,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search)"_s)},
            {u"mode"_s,
             McpProtocolServerTool::schemaEnumProperty({inlineMode, attachmentMode},
                                                       u"How the mail is forwarded: inline (quoted in the body, default) or attachment (attached as is)"_s)}},
        {u"id"_s});
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void ForwardMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    bool asAttachment = false;
    if (const QJsonValue modeValue = arguments.value(u"mode"_s); TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(modeValue)) {
        const QString mode = modeValue.toString();
        if (mode == attachmentMode) {
            asAttachment = true;
        } else if (mode != inlineMode) {
            call->finishWithText(i18n("Argument mode must be one of: inline, attachment"), true);
            return;
        }
    }

    auto job = new ForwardMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setAsAttachment(asAttachment);
    job->start();
}
