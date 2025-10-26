/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichatcalendarpluginutils.h"
#include "kaichat_addressbookplugin_debug.h"

using namespace Qt::Literals::StringLiterals;
QString KAIChatCalendarPluginUtils::convertAddressBookEnumToString(AddressBookEnum type)
{
    switch (type) {
    case Email:
        return u"email"_s;
    case Birthday:
        return u"birthday"_s;
    case Unknown:
        break;
    }
    Q_UNREACHABLE();
    return {};
}

KAIChatCalendarPluginUtils::AddressBookEnum KAIChatCalendarPluginUtils::convertStringToAddressBookEnum(const QString &str)
{
    if (str == "email"_L1) {
        return KAIChatCalendarPluginUtils::AddressBookEnum::Email;
    } else if (str == "birthday"_L1) {
        return KAIChatCalendarPluginUtils::AddressBookEnum::Birthday;
    } else {
        qCWarning(KAICHAT_ADDRESSBOOK_LOG) << "Invalid AddressBook type:" << str;
        return KAIChatCalendarPluginUtils::AddressBookEnum::Unknown;
    }
    return KAIChatCalendarPluginUtils::AddressBookEnum::Unknown;
}
