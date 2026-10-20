/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "editmailtool.h"
#include "common/toolutils.h"
#include "editmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

EditMailTool::EditMailTool() = default;
EditMailTool::~EditMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool EditMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_edit"_s,
        u"Open a draft mail in a KMail composer to modify it (subject, recipients, body), KMail is started if needed. Use this tool, not mail_open, to modify "
        u"a mail. Only mails stored in a Drafts folder can be edited "
        u"(for example the ones created with mail_create), other mails are refused; use mail_open or mail_reply for them"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the draft mail item (see mail_create or mail_search)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Edit Mail"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void EditMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    auto job = new EditMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->start();
}
