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

#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <CalendarEvents/CalendarEventsPlugin>
#include <QDebug>
#include <QTest>

QDebug operator<<(QDebug dbg, const CalendarEvents::EventData &data)
{
    dbg.nospace() << data.title() << " (UID " << data.uid() << "), "
                  << data.startDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t"))
                  << " - "
                  << data.endDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t"));
    return dbg;
}

bool operator==(const CalendarEvents::EventData &lhs, const CalendarEvents::EventData &rhs)
{
    return lhs.uid() == rhs.uid()
            && lhs.type() == rhs.type()
            && lhs.isAllDay() == rhs.isAllDay()
            && lhs.isMinor() == rhs.isMinor()
            && lhs.title() == rhs.title()
            && lhs.startDateTime() == rhs.startDateTime()
            && lhs.endDateTime() == rhs.endDateTime()
            && lhs.description() == rhs.description()
            && lhs.eventColor() == rhs.eventColor();
}

namespace std
{
bool operator<(const CalendarEvents::EventData &lhs, const CalendarEvents::EventData &rhs)
{
    if (lhs.startDateTime() != rhs.startDateTime()) {
        return lhs.startDateTime() < rhs.startDateTime();
    } else if (lhs.endDateTime() != rhs.endDateTime()) {
        return lhs.endDateTime() < rhs.endDateTime();
    } else {
        return lhs.uid() < rhs.uid();
    }
}
}

#define COMPARE(_actual, _expected) \
{ \
    bool ok = false; \
    [&]() { \
        QCOMPARE(_actual, _expected); \
        ok = true; \
    }(); \
    if (!ok) { \
        return false; \
    } \
}

#define VERIFY(_cond) \
{ \
    bool ok = false; \
    [&]() { \
        QVERIFY(_cond); \
        ok = true; \
    }(); \
    if (!ok) { \
        return false; \
    } \
}

namespace TestUtils
{

bool compareEventData(const CalendarEvents::EventData &actual,
                      const CalendarEvents::EventData &expected)
{
    COMPARE(actual.title(), expected.title());
    COMPARE(actual.description(), expected.description());
    COMPARE(actual.isAllDay(), expected.isAllDay());
    COMPARE(actual.isMinor(), expected.isMinor());
    COMPARE(actual.type(), expected.type());
    COMPARE(actual.eventColor(), expected.eventColor());
    COMPARE(actual.uid(), expected.uid());
    COMPARE(actual.startDateTime(), expected.startDateTime());
    COMPARE(actual.endDateTime(), expected.endDateTime());

    return true;
}

}


#endif
