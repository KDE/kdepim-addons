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

#include "fakepimdatasource.h"

#include <KCalCore/MemoryCalendar>

FakePimDataSource::FakePimDataSource()
    : PimDataSource()
    , mCalendar(new KCalCore::MemoryCalendar(KDateTime::UTC))
{
}

FakePimDataSource::~FakePimDataSource()
{
    delete mCalendar;
}

void FakePimDataSource::setAkonadiIdForIncidence(const KCalCore::Incidence::Ptr &incidence, qint64 akonadiId)
{
    mAkonadiIdMap.insert(incidence, akonadiId);
}

qint64 FakePimDataSource::akonadiIdForIncidence(const KCalCore::Incidence::Ptr &incidence) const
{
    return mAkonadiIdMap.value(incidence, -1);
}

KCalCore::Calendar *FakePimDataSource::calendar() const
{
    return mCalendar;
}
