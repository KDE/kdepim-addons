/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "listidentitiestool.h"
#include <KIdentityManagementCore/IdentityManager>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
ListIdentitiesTool::ListIdentitiesTool() = default;
ListIdentitiesTool::~ListIdentitiesTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ListIdentitiesTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"mail_list_identities"_s, u"List the identities"_s);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("List Identities"));
    tool.setAnnotations(annotation);
    return tool;
}

void ListIdentitiesTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto list = KIdentityManagementCore::IdentityManager::self();
    QStringList entries;
    if (entries.isEmpty()) {
        call->finishWithText(i18n("No Identity found"));
    } else {
        call->finishWithText(entries.join(u'\n'));
    }
}
