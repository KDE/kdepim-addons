/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include <CalendarEvents/CalendarEventsPlugin>
#include <QDebug>
#include <QTest>

QDebug operator<<(QDebug dbg, const CalendarEvents::EventData &data)
{
    dbg.nospace() << data.title() << " (UID " << data.uid() << "), " << data.startDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t")) << " - "
                  << data.endDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t"));
    return dbg;
}

namespace CalendarEvents
{
bool operator==(const EventData &lhs, const EventData &rhs)
{
    return lhs.uid() == rhs.uid() && lhs.type() == rhs.type() && lhs.isAllDay() == rhs.isAllDay() && lhs.isMinor() == rhs.isMinor()
        && lhs.title() == rhs.title() && lhs.startDateTime() == rhs.startDateTime() && lhs.endDateTime() == rhs.endDateTime()
        && lhs.description() == rhs.description() && lhs.eventColor() == rhs.eventColor();
}

bool operator<(const EventData &lhs, const EventData &rhs)
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

#define COMPARE(_actual, _expected)                                                                                                                            \
    {                                                                                                                                                          \
        bool ok = false;                                                                                                                                       \
        [&]() {                                                                                                                                                \
            QCOMPARE(_actual, _expected);                                                                                                                      \
            ok = true;                                                                                                                                         \
        }();                                                                                                                                                   \
        if (!ok) {                                                                                                                                             \
            return false;                                                                                                                                      \
        }                                                                                                                                                      \
    }

#define VERIFY(_cond)                                                                                                                                          \
    {                                                                                                                                                          \
        bool ok = false;                                                                                                                                       \
        [&]() {                                                                                                                                                \
            QVERIFY(_cond);                                                                                                                                    \
            ok = true;                                                                                                                                         \
        }();                                                                                                                                                   \
        if (!ok) {                                                                                                                                             \
            return false;                                                                                                                                      \
        }                                                                                                                                                      \
    }

namespace TestUtils
{
bool compareEventData(const CalendarEvents::EventData &actual, const CalendarEvents::EventData &expected)
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

