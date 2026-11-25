/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadimcpcommandlineparser.h"
#include <KLocalizedString>
#include <QCommandLineOption>
#include <QCommandLineParser>
#if TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION < QT_VERSION_CHECK(2, 3, 47)
#include <QTextStream>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
#include <algorithm>
#endif
using namespace Qt::Literals::StringLiterals;

AkonadiMcpCommandLineParser::AkonadiMcpCommandLineParser(QCommandLineParser *parser)
{
    initializeCommandLine(parser);
}

AkonadiMcpCommandLineParser::~AkonadiMcpCommandLineParser() = default;

void AkonadiMcpCommandLineParser::initializeCommandLine(QCommandLineParser *parser)
{
    parser->addOption(
        QCommandLineOption(QStringList() << optionParserFromEnum(OptionParser::Url), i18nc("@info:shell", "Url where server listens."), u"url"_s));
    parser->addOption(
        QCommandLineOption(QStringList() << optionParserFromEnum(OptionParser::ListTools), i18nc("@info:shell", "List supported MCP tools and exit.")));
}

QString AkonadiMcpCommandLineParser::optionParserFromEnum(OptionParser e)
{
    switch (e) {
    case OptionParser::ListTools:
        return u"list-tools"_s;
    case OptionParser::Url:
        return u"url"_s;
    }
    return {};
}

#if TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION < QT_VERSION_CHECK(2, 3, 47)
void AkonadiMcpCommandLineParser::printTools(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> &lst)
{
    qsizetype nameWidth = 0;
    for (const auto &tool : lst) {
        nameWidth = std::max(nameWidth, tool.name().size());
    }
    QTextStream out(stdout);
    out << i18n("List of Tools:") << '\n';
    for (const auto &tool : lst) {
        out << "   " << tool.name().leftJustified(nameWidth) << "   " << tool.description().value_or(tool.title().value_or(QString())) << '\n';
    }
}
#endif
