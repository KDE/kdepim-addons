/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QString>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolMeta;
class McpProtocolTool;
}
namespace ToolUtils
{
enum TitleType : uint8_t {
    Mail,
    Contact,
    Calendar,
    Akonadi,
};

void addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &meta, TitleType type);
// Add group meta to the tool, existing meta values are kept.
void addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &tool, TitleType type);
[[nodiscard]] QString groupFromType(TitleType type);
[[nodiscard]] QString groupTitleFromType(TitleType type);
}
