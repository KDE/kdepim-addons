/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "toolutils.h"
#include <QJsonArray>

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
