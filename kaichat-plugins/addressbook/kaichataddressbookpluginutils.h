/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QString>
namespace KAIChatAddressBookPluginUtils
{
enum AddressBookInformationTypeEnum : int8_t {
    Unknown = 0,
    Email,
    Birthday,
    Address,
    // TODO add more
};
[[nodiscard]] QString convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum type);
[[nodiscard]] KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum convertStringToAddressBookEnum(const QString &str);

enum AddressBookPropertyNameEnum : int8_t {
    UserName = 0,
    AddressBookInfo,
};
[[nodiscard]] QString convertAddressBookPropertyNameEnumToString(KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum type);
[[nodiscard]] KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum convertStringToAddressBookPropertyNameEnum(const QString &str);
};
