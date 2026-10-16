/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "replymailtool.h"
#include "replymailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>
#include <algorithm>

using namespace Qt::Literals::StringLiterals;

namespace
{
struct StrategyName {
    QString name;
    ReplyMailToolJob::ReplyStrategy strategy;
};

const StrategyName strategyNames[] = {
    {u"smart"_s, ReplyMailToolJob::ReplyStrategy::ReplySmart},
    {u"author"_s, ReplyMailToolJob::ReplyStrategy::ReplyAuthor},
    {u"list"_s, ReplyMailToolJob::ReplyStrategy::ReplyList},
    {u"all"_s, ReplyMailToolJob::ReplyStrategy::ReplyAll},
};
}

ReplyMailTool::ReplyMailTool() = default;
ReplyMailTool::~ReplyMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ReplyMailTool::definition() const
{
    QStringList strategies;
    for (const auto &strategyName : strategyNames) {
        strategies.append(strategyName.name);
    }
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_reply"_s,
        u"Open a KMail composer to reply to a mail, KMail is started if needed. The reply is not sent"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail item (see mail_search)"_s)},
            {u"strategy"_s,
             McpProtocolServerTool::schemaEnumProperty(strategies,
                                                       u"Recipients of the reply: smart (guess the best recipient, default), author (only the author), "
                                                       u"list (only the mailing list), all (author and all recipients)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Reply to Mail"));
    tool.setAnnotations(annotation);
    return tool;
}

void ReplyMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
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

    auto strategy = ReplyMailToolJob::ReplyStrategy::ReplySmart;
    if (const QJsonValue strategyValue = arguments.value(u"strategy"_s); !strategyValue.isNull() && !strategyValue.isUndefined()) {
        const QString strategyText = strategyValue.toString();
        const auto it = std::find_if(std::begin(strategyNames), std::end(strategyNames), [&strategyText](const StrategyName &strategyName) {
            return strategyName.name == strategyText;
        });
        if (it == std::end(strategyNames)) {
            call->finishWithText(i18n("Argument strategy must be one of: smart, author, list, all"), true);
            return;
        }
        strategy = it->strategy;
    }

    auto job = new ReplyMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setReplyStrategy(strategy);
    job->start();
}
