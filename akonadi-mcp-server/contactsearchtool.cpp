/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactsearchtool.h"

using namespace Qt::Literals::StringLiterals;
ContactSearchTool::ContactSearchTool() = default;
ContactSearchTool::~ContactSearchTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ContactSearchTool::definition() const
{
    return TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_search"_s,
        u"Search contacts in the Akonadi address books by name or email address"_s,
        QMap<QString, QJsonObject>{
            {u"query"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Name or email address to search for"_s)}},
        {u"query"_s});
}

void ContactSearchTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    // TODO search in akonadi the user
}