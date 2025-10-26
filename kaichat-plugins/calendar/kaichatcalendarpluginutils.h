/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QString>
namespace KAIChatCalendarPluginUtils
{
enum AddressBookEnum : int8_t {
    Unknown = 0,
    Email,
    Birthday
    // TODO add more
};
[[nodiscard]] QString convertAddressBookEnumToString(KAIChatCalendarPluginUtils::AddressBookEnum type);
[[nodiscard]] KAIChatCalendarPluginUtils::AddressBookEnum convertStringToAddressBookEnum(const QString &str);
};
