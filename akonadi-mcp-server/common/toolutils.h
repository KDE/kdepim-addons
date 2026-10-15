/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStringList>

class QJsonValue;

namespace ToolUtils
{
// Append the non-empty trimmed strings of a JSON array to list.
// An undefined or null value is accepted, returns false if value is not an array of strings.
[[nodiscard]] bool readStringList(const QJsonValue &value, QStringList &list);
}
