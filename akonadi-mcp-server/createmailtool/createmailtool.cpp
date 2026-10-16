/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createmailtool.h"
#include "common/toolutils.h"
#include "createmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

CreateMailTool::CreateMailTool() = default;
CreateMailTool::~CreateMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_create"_s,
        u"Create a new mail and store it in the default Drafts folder, the mail is not sent. Use mail_edit to open it in a KMail composer"_s,
        QMap<QString, QJsonObject>{
            {u"subject"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Subject of the mail"_s)},
            {u"to"_s, McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}), u"Recipient addresses"_s)},
            {u"cc"_s, McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}), u"Carbon copy addresses"_s)},
            {u"bcc"_s, McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}), u"Blind carbon copy addresses"_s)},
            {u"body"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Plain text message of the mail"_s)}},
        {u"subject"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Create Mail"));
    tool.setAnnotations(annotation);
    return tool;
}

void CreateMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString subject = arguments.value(u"subject"_s).toString().trimmed();
    if (subject.isEmpty()) {
        call->finishWithText(i18n("Argument subject must be a non-empty string"), true);
        return;
    }

    QStringList to;
    if (!ToolUtils::readStringList(arguments.value(u"to"_s), to)) {
        call->finishWithText(i18n("Argument to must be an array of strings"), true);
        return;
    }
    QStringList cc;
    if (!ToolUtils::readStringList(arguments.value(u"cc"_s), cc)) {
        call->finishWithText(i18n("Argument cc must be an array of strings"), true);
        return;
    }
    QStringList bcc;
    if (!ToolUtils::readStringList(arguments.value(u"bcc"_s), bcc)) {
        call->finishWithText(i18n("Argument bcc must be an array of strings"), true);
        return;
    }

    const QJsonValue bodyValue = arguments.value(u"body"_s);
    if (!bodyValue.isString() && !bodyValue.isUndefined() && !bodyValue.isNull()) {
        call->finishWithText(i18n("Argument body must be a string"), true);
        return;
    }

    auto job = new CreateMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setSubject(subject);
    job->setTo(to);
    job->setCc(cc);
    job->setBcc(bcc);
    job->setBody(bodyValue.toString());
    job->start();
}
