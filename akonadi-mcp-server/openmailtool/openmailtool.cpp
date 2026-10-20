/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openmailtool.h"
#include "common/toolutils.h"
#include "openmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

OpenMailTool::OpenMailTool() = default;
OpenMailTool::~OpenMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool OpenMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_open"_s,
        u"Display a mail in a read-only KMail viewer window, KMail is started if needed. The mail can't be modified there: "
        u"use mail_edit to modify a draft mail (for example one created with mail_create) and mail_reply to answer a mail"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search or mail_create)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Open Mail"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void OpenMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    auto job = new OpenMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->start();
}
