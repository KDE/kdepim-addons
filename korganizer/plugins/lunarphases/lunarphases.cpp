/*
  Copyright (c) 2018 Allen Winter <winter@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "lunarphases.h"

#include <KHolidays/LunarPhase>

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>

Lunarphases::Lunarphases()
{
    KConfig _config(QStringLiteral("korganizerrc"));
    KConfigGroup config(&_config, "Lunar Phases Plugin");
}

QString Lunarphases::info() const
{
    return i18n("This plugin displays the day's lunar phase (New, First, Last, Full). "
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
