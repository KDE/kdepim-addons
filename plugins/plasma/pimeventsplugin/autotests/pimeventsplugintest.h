/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include <KCalendarCore/Event>
#include <QMultiHash>
#include <QObject>

class QDate;
namespace CalendarEvents
{
class EventData;
}
class FakePimDataSource;

using DateEventDataHash = QMultiHash<QDate, CalendarEvents::EventData>;

class PimEventsPluginTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void testLoadEventsForDataRange();
    void testEventAdded();
    void testEventModified();
    void testEventRemoved();

private:
    [[nodiscard]] bool compareEventDataHashes(const DateEventDataHash &actual, const DateEventDataHash &expected);
    [[nodiscard]] DateEventDataHash populateCalendar(FakePimDataSource *source, bool uniqueEventData);
    [[nodiscard]] QList<CalendarEvents::EventData> findEventData(const KCalendarCore::Event::Ptr &event, const DateEventDataHash &allData);
};
