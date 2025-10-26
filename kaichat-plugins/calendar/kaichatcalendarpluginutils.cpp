/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichatcalendarpluginutils.h"
#include "kaichat_calendarplugin_debug.h"

using namespace Qt::Literals::StringLiterals;
QString KAIChatCalendarPluginUtils::convertCalendarEnumToString(CalendarEnum type)
{
    switch (type) {
    case Email:
        return u"email"_s;
    case Unknown:
        break;
    }
    Q_UNREACHABLE();
    return {};
}

KAIChatCalendarPluginUtils::CalendarEnum KAIChatCalendarPluginUtils::convertStringToCalendarEnum(const QString &str)
{
    if (str == "email"_L1) {
        return KAIChatCalendarPluginUtils::CalendarEnum::Email;
    } else {
        qCWarning(KAICHAT_CALENDAR_LOG) << "Invalid calendar type:" << str;
        return KAIChatCalendarPluginUtils::CalendarEnum::Unknown;
    }
    return KAIChatCalendarPluginUtils::CalendarEnum::Unknown;
}
