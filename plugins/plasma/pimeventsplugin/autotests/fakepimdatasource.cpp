/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "fakepimdatasource.h"

#include <KCalendarCore/MemoryCalendar>
#include <QTimeZone>

FakePimDataSource::FakePimDataSource()
    : PimDataSource()
    , mCalendar(new KCalendarCore::MemoryCalendar(QTimeZone::systemTimeZone()))
{
}

FakePimDataSource::~FakePimDataSource()
{
    delete mCalendar;
}

void FakePimDataSource::setAkonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence, qint64 akonadiId)
{
    mAkonadiIdMap.insert(incidence, akonadiId);
}

qint64 FakePimDataSource::akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const
{
    return mAkonadiIdMap.value(incidence, -1);
}

KCalendarCore::Calendar *FakePimDataSource::calendar() const
{
    return mCalendar;
}

QString FakePimDataSource::calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &) const
{
    return QString();
}
