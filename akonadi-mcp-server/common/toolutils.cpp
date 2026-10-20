/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "toolutils.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCommonUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
using namespace Qt::Literals::StringLiterals;
bool ToolUtils::readStringList(const QJsonValue &value, QStringList &list)
{
    if (value.isUndefined() || value.isNull()) {
        return true;
    }
    if (!value.isArray()) {
        return false;
    }
    const QJsonArray array = value.toArray();
    for (const QJsonValue &element : array) {
        if (!element.isString()) {
            return false;
        }
        if (const QString str = element.toString().trimmed(); !str.isEmpty()) {
            list.append(str);
        }
    }
    return true;
}

bool ToolUtils::isProvided(const QJsonValue &value)
{
    return !value.isUndefined() && !value.isNull();
}

bool ToolUtils::readOptionalString(const QMap<QString, QJsonValue> &arguments, const QString &key, std::optional<QString> &result)
{
    const QJsonValue value = arguments.value(key);
    if (!isProvided(value)) {
        return true;
    }
    if (!value.isString()) {
        return false;
    }
    result = value.toString().trimmed();
    return true;
}

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
    TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta meta = tool.meta().value_or(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta{});
    addToolMeta(meta, type);
    tool.setMeta(meta);
}
