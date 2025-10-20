/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QString>
namespace KAIChatAddressBookPluginUtils
{
enum AddressBookEnum : int8_t {
    Unknown = 0,
    Email,
    // TODO add more
};
[[nodiscard]] QString convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::AddressBookEnum type);
[[nodiscard]] KAIChatAddressBookPluginUtils::AddressBookEnum convertStringToAddressBookEnum(const QString &str);
};
