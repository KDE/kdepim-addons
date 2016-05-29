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

#ifndef EVENTDATAVISITORTEST_H
#define EVENTDATAVISITORTEST_H

#include <QObject>

namespace CalendarEvents
{
class EventData;
}

class EventDataVisitorTest : public QObject
{
    Q_OBJECT


private Q_SLOTS:
    void testGenerateUID_data();
    void testGenerateUID();

    void testIsInRange_data();
    void testIsInRange();

    void testExplodeIncidenceOccurences_data();
    void testExplodeIncidenceOccurences();

    void testEventDataVisitor_data();
    void testEventDataVisitor();

    void testEventDataIdVisitor_data();
    void testEventDataIdVisitor();

private:
    bool compareResults(const CalendarEvents::EventData &actual,
                        const CalendarEvents::EventData &expected);
};

#endif
