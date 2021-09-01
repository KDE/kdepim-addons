/*
  SPDX-FileCopyrightText: 2018 Allen Winter <winter@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lunarphases.h"

#include <KHolidays/LunarPhase>

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>

K_PLUGIN_FACTORY(LunarphasesFactory, registerPlugin<Lunarphases>();)

Lunarphases::Lunarphases(QObject *parent, const QVariantList &args)
    : Decoration(parent, args)
{
    KConfig _config(QStringLiteral("korganizerrc"));
    KConfigGroup config(&_config, "Lunar Phases Plugin");
}

QString Lunarphases::info() const
{
    return i18n(
        "This plugin displays the day's lunar phase (New, First, Last, Full). "
        "Currently, the phase is computed for noon at UTC; therefore, you should "
        "expect variations by 1 day in either direction.");
}

Element::List Lunarphases::createDayElements(const QDate &date)
{
    Element::List result;

    const QString name = KHolidays::LunarPhase::phaseNameAtDate(date);
    StoredElement *e = new StoredElement(QStringLiteral("main element"), name, name);

    result.append(e);
    return result;
}

Element::List Lunarphases::createWeekElements(const QDate &date)
{
    Element::List result;

    const QString name = KHolidays::LunarPhase::phaseNameAtDate(date);
    StoredElement *e = new StoredElement(QStringLiteral("main element"), name, name);
    result.append(e);

    return result;
}

#include "lunarphases.moc"
