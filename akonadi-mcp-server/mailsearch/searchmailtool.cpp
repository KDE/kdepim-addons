/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "searchmailtool.h"
#include "searchmailtooljob.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
SearchMailTool::SearchMailTool() = default;
SearchMailTool::~SearchMailTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool SearchMailTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"search_mail"_s, u"List the Akonadi address books"_s);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Search Mail"));
    tool.setAnnotations(annotation);
    return tool;
}

void SearchMailTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();

    auto job = new SearchMailToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->start();
    // TODO
}
