/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QList>
#include <QString>
#include <cstdint>
class QCommandLineParser;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolTool;
}
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
    static void printTools(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> &lst);

private:
    void initializeCommandLine(QCommandLineParser *parser);
};
