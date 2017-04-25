/*
 * Copyright (C) 2016  Daniel Vrátil <dvratil@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef PIMDATASOURCE_H
#define PIMDATASOURCE_H

#include <KCalCore/Incidence>

namespace KCalCore {
class Calendar;
}

class PimDataSource
{
public:
    virtual ~PimDataSource()
    {
    }

    virtual KCalCore::Calendar *calendar() const = 0;
    virtual qint64 akonadiIdForIncidence(const KCalCore::Incidence::Ptr &incidence) const = 0;
    virtual QString calendarColorForIncidence(const KCalCore::Incidence::Ptr &incidence) const = 0;
};

#endif
