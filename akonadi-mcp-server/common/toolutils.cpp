/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "toolutils.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCommonUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
using namespace Qt::Literals::StringLiterals;

QString ToolUtils::groupTitleFromType(TitleType type)
{
    switch (type) {
    case Mail:
        return i18n("Mail");
    case Contact:
        return i18n("Contact");
    case Calendar:
        return i18n("Calendar");
    case Akonadi:
        return i18n("Akonadi");
    }
    Q_UNREACHABLE();
    return {};
}

QString ToolUtils::groupFromType(TitleType type)
{
    switch (type) {
    case Mail:
        return u"mail"_s;
    case Contact:
        return u"contact"_s;
    case Calendar:
        return u"calendar"_s;
    case Akonadi:
        return u"akonadi"_s;
    }
    Q_UNREACHABLE();
    return {};
}

void ToolUtils::addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &meta, TitleType type)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::addToolMeta(meta, groupFromType(type), groupTitleFromType(type));
}

void ToolUtils::addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &tool, TitleType type)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::addToolMeta(tool, groupFromType(type), groupTitleFromType(type));
}
