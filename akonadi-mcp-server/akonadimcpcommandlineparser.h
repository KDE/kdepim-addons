/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_version.h"
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
#if TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION < QT_VERSION_CHECK(2, 3, 47)
    static void printTools(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> &lst);
#endif

private:
    void initializeCommandLine(QCommandLineParser *parser);
};
