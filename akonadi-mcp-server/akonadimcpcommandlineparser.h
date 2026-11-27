/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "config-kdepim-addons.h"
#include <QList>
#include <QString>
#include <cstdint>
class QCommandLineParser;
#if !HAVE_MCP_TOOL_LIST
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolTool;
}
#endif
class AkonadiMcpCommandLineParser
{
public:
    enum class OptionParser : uint8_t {
        ListTools = 0,
        Url,
    };

    explicit AkonadiMcpCommandLineParser(QCommandLineParser *parser);
    ~AkonadiMcpCommandLineParser();

    [[nodiscard]] static QString optionParserFromEnum(OptionParser e);
#if !HAVE_MCP_TOOL_LIST
    static void printTools(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> &lst);
#endif

private:
    void initializeCommandLine(QCommandLineParser *parser);
};
