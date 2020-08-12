/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#ifndef EVENTDATAVISITORTEST_H
#define EVENTDATAVISITORTEST_H

#include <QObject>

namespace CalendarEvents {
class EventData;
}

class EventDataVisitorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();

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
};

#endif
