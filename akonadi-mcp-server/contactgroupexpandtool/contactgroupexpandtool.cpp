/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactgroupexpandtool.h"
#include "common/toolutils.h"
#include "contactgroupexpandtooljob.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
ContactGroupExpandTool::ContactGroupExpandTool() = default;
ContactGroupExpandTool::~ContactGroupExpandTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ContactGroupExpandTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_group_expand"_s,
        u"Search contact group in the Akonadi address books by name and expand it"_s,
        QMap<QString, QJsonObject>{
            {u"query"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Group name to search for"_s)}},
        {u"query"_s});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Search Contact Group"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void ContactGroupExpandTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QString query = call->arguments().value(u"query"_s).toString().trimmed();
    if (query.isEmpty()) {
        call->finishWithText(i18n("Argument query must be a non-empty string"), true);
        return;
    }

    auto job = new ContactGroupExpandToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setGroupName(query);
    job->start();
}
