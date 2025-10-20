/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginutils.h"
#include "kaichat_addressbookplugin_debug.h"

using namespace Qt::Literals::StringLiterals;
QString KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(AddressBookEnum type)
{
    switch (type) {
    case Email:
        return u"email"_s;
#if 0
    case Date:
        return u"date"_s;
    case DateTime:
        return u"date and time"_s;
#endif
    case Unknown:
        break;
    }
    Q_UNREACHABLE();
    return {};
}

KAIChatAddressBookPluginUtils::AddressBookEnum KAIChatAddressBookPluginUtils::convertStringToAddressBookEnum(const QString &str)
{
    if (str == "email"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookEnum::Email;
#if 0
    } else if (str == "date"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookEnum::Date;
    } else if (str == "date and time"_L1) {
        return KAIChatAddressBookPluginUtils::AddressBookEnum::DateTime;
    } else {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid date time type:" << str;
        return KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown;
#endif
    }
    return KAIChatAddressBookPluginUtils::AddressBookEnum::Unknown;
}
