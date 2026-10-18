/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QJsonValue>
#include <QMap>
#include <QStringList>
#include <optional>

namespace ToolUtils
{
// Append the non-empty trimmed strings of a JSON array to list.
// An undefined or null value is accepted, returns false if value is not an array of strings.
[[nodiscard]] bool readStringList(const QJsonValue &value, QStringList &list);
// Returns true if the value is neither undefined nor null
[[nodiscard]] bool isProvided(const QJsonValue &value);
// Set result to the trimmed string when the argument is provided, an empty string is a valid value.
// Returns false if the argument is provided but is not a string.
[[nodiscard]] bool readOptionalString(const QMap<QString, QJsonValue> &arguments, const QString &key, std::optional<QString> &result);
}
