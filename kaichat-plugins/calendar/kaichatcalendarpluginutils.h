/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QString>
namespace KAIChatCalendarPluginUtils
{
enum CalendarEnum : int8_t {
    Unknown = 0,
    Email,
    Birthday
    // TODO add more
};
[[nodiscard]] QString convertCalendarEnumToString(KAIChatCalendarPluginUtils::CalendarEnum type);
[[nodiscard]] KAIChatCalendarPluginUtils::CalendarEnum convertStringToCalendarEnum(const QString &str);
};
