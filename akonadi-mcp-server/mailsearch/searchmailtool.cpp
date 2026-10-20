/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "searchmailtool.h"
#include "common/toolutils.h"
#include "searchmailtooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int defaultLimit = 20;
constexpr int maximumLimit = 100;
}
SearchMailTool::SearchMailTool() = default;
SearchMailTool::~SearchMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool SearchMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_search"_s,
        u"Search mails in the Akonadi mail folders by subject, sender, recipient or body text, most recent first"_s,
        QMap<QString, QJsonObject>{
            {u"query"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Text to search for"_s)},
            {u"field"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaEnumProperty({u"all"_s, u"subject"_s, u"from"_s, u"to"_s, u"body"_s},
                                                                                            u"Mail field to search in (default all)"_s)},
            {u"limit"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                                                        u"Maximum number of mails to return, from 1 to 100 (default 20)"_s)}},
        {u"query"_s});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Search Mail"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void SearchMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString query = arguments.value(u"query"_s).toString().trimmed();
    if (query.isEmpty()) {
        call->finishWithText(i18n("Argument query must be a non-empty string"), true);
        return;
    }

    SearchMailToolJob::SearchField searchField = SearchMailToolJob::SearchField::All;
    const QJsonValue fieldValue = arguments.value(u"field"_s);
    if (fieldValue.isString()) {
        const QString fieldName = fieldValue.toString();
        if (fieldName == "all"_L1) {
            searchField = SearchMailToolJob::SearchField::All;
        } else if (fieldName == "subject"_L1) {
            searchField = SearchMailToolJob::SearchField::Subject;
        } else if (fieldName == "from"_L1) {
            searchField = SearchMailToolJob::SearchField::From;
        } else if (fieldName == "to"_L1) {
            searchField = SearchMailToolJob::SearchField::To;
        } else if (fieldName == "body"_L1) {
            searchField = SearchMailToolJob::SearchField::Body;
        } else {
            call->finishWithText(i18n("Unknown mail field: %1", fieldName), true);
            return;
        }
    } else if (!fieldValue.isUndefined() && !fieldValue.isNull()) {
        call->finishWithText(i18n("Argument field must be a string"), true);
        return;
    }

    int limit = defaultLimit;
    const QJsonValue limitValue = arguments.value(u"limit"_s);
    if (limitValue.isDouble()) {
        limit = limitValue.toInt(-1);
        if (limit < 1 || limit > maximumLimit) {
            call->finishWithText(i18n("Argument limit must be an integer between 1 and %1", maximumLimit), true);
            return;
        }
    } else if (!limitValue.isUndefined() && !limitValue.isNull()) {
        call->finishWithText(i18n("Argument limit must be an integer"), true);
        return;
    }

    auto job = new SearchMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setSearchString(query);
    job->setSearchField(searchField);
    job->setLimit(limit);
    job->start();
}
