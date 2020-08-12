/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#ifndef PIMDATASOURCE_H
#define PIMDATASOURCE_H

#include <KCalendarCore/Incidence>

namespace KCalendarCore {
class Calendar;
}

class PimDataSource
{
public:
    virtual ~PimDataSource()
    {
    }

    virtual KCalendarCore::Calendar *calendar() const = 0;
    virtual qint64 akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const = 0;
    virtual QString calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const = 0;
};

#endif
