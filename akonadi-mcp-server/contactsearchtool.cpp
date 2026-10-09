/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactsearchtool.h"

ContactSearchTool::ContactSearchTool() = default;
ContactSearchTool::~ContactSearchTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ContactSearchTool::definition() const
{
    // TODO define it
    return {};
}

void ContactSearchTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    // TODO search in akonadi the user
}