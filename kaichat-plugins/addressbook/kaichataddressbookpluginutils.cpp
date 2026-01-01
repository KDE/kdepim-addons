/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginutils.h"
#include "kaichat_addressbookplugin_debug.h"

using namespace Qt::Literals::StringLiterals;
QString KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(AddressBookInformationTypeEnum type)
{
    switch (type) {
    case Email:
        return u"email"_s;
    case Birthday:
        return u"birthday"_s;
    case Address:
        return u"address"_s;
    case Unknown:
        break;
    }
    Q_UNREACHABLE();
    return {};
}

KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum KAIChatAddressBookPluginUtils::convertStringToAddressBookEnum(const QString &str)
{
    if (str == "email"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum::Email;
    } else if (str == "birthday"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum::Birthday;
    } else if (str == "address"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum::Address;
    } else {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid AddressBook type:" << str;
        return KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum::Unknown;
    }
    return KAIChatAddressBookPluginUtils::AddressBookInformationTypeEnum::Unknown;
}

QString KAIChatAddressBookPluginUtils::convertAddressBookPropertyNameEnumToString(KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum type)
{
    switch (type) {
    case UserName:
        return u"username"_s;
    case AddressBookInfo:
        return u"addressbookinfo"_s;
    }
    Q_UNREACHABLE();
    return {};
}

KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum KAIChatAddressBookPluginUtils::convertStringToAddressBookPropertyNameEnum(const QString &str)
{
    if (str == "username"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum::UserName;
    } else if (str == "addressbookinfo"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum::AddressBookInfo;
    } else {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid AddressBook type:" << str;
        return KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum::UserName;
    }
    return KAIChatAddressBookPluginUtils::AddressBookPropertyNameEnum::UserName;
}
