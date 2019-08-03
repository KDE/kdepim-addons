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

#ifndef FAKEPIMDATASOURCE_H
#define FAKEPIMDATASOURCE_H

#include "pimdatasource.h"

class FakePimDataSource : public PimDataSource
{
public:
    FakePimDataSource();
    ~FakePimDataSource() override;

    void setAkonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence, qint64 akonadiId);
    qint64 akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

    KCalendarCore::Calendar *calendar() const override;

    QString calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

private:
    QMap<KCalendarCore::Incidence::Ptr, qint64> mAkonadiIdMap;
    KCalendarCore::Calendar *mCalendar = nullptr;
};

#endif
