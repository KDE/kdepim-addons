/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "pimeventsplugintest.h"
#include "../pimeventsplugin.h"
#include "fakepimdatasource.h"
#include "testdataparser.h"
#include "testutils.h"

#include <QSignalSpy>
#include <QTest>

Q_DECLARE_METATYPE(DateEventDataHash)
Q_DECLARE_METATYPE(CalendarEvents::EventData)

void PimEventsPluginTest::initTestCase()
{
    qputenv("TZ", "Europe/Berlin");
    qRegisterMetaType<DateEventDataHash>("QMultiHash<QDate, CalendarEvents::EventData>");
    qRegisterMetaType<CalendarEvents::EventData>("CalendarEvents::EventData");
}

bool PimEventsPluginTest::compareEventDataHashes(const DateEventDataHash &actual, const DateEventDataHash &expected)
{
    COMPARE(actual.size(), expected.size());
    for (const QDate &resultKey : actual.uniqueKeys()) {
        VERIFY(expected.contains(resultKey));
        auto resultValues = actual.values(resultKey);
        auto expectedValues = expected.values(resultKey);
        COMPARE(resultValues.size(), expectedValues.size());
        std::sort(resultValues.begin(), resultValues.end(), std::less<CalendarEvents::EventData>());
        std::sort(expectedValues.begin(), expectedValues.end(), std::less<CalendarEvents::EventData>());
        COMPARE(resultValues, expectedValues);
    }
    return true;
}

DateEventDataHash PimEventsPluginTest::populateCalendar(FakePimDataSource *source, bool uniqueEventData)
{
    const QStringList allData = TestDataParser::allTestData();
    DateEventDataHash expectedData;
    for (const QString &data : allData) {
        TestDataParser parser(data, true);
        if (parser.rangeEnd() < QDate(2016, 5, 1) || parser.rangeStart() > QDate(2016, 5, 31)) {
            continue;
        }
        const KCalendarCore::Event::Ptr event = parser.incidence().dynamicCast<KCalendarCore::Event>();
        if (event) {
            source->setAkonadiIdForIncidence(event, parser.akonadiId());
            source->calendar()->addEvent(event);
            for (const CalendarEvents::EventData &dt : parser.eventData()) {
                if (uniqueEventData) {
                    expectedData.insert(dt.startDateTime().date(), dt);
                } else {
                    QDate d = dt.startDateTime().date();
                    while (d <= dt.endDateTime().date()) {
                        expectedData.insert(d, dt);
                        d = d.addDays(1);
                    }
                }
            }
        }
    }

    return expectedData;
}

QList<CalendarEvents::EventData> PimEventsPluginTest::findEventData(const KCalendarCore::Event::Ptr &event, const DateEventDataHash &allData)
{
    QList<CalendarEvents::EventData> data;
    for (auto it = allData.cbegin(), end = allData.cend(); it != end; ++it) {
        // This is a very naive check
        if (it->title() == event->summary() && it->description() == event->description() && it->isAllDay() == event->allDay()) {
            data.push_back((*it));
        }
    }

    return data;
}

void PimEventsPluginTest::testLoadEventsForDataRange()
{
    FakePimDataSource source;
    const DateEventDataHash expectedData = populateCalendar(&source, false);

    PimEventsPlugin plugin(&source);
    QSignalSpy dataReadySpy(&plugin, &PimEventsPlugin::dataReady);
    QVERIFY(dataReadySpy.isValid());

    plugin.loadEventsForDateRange(QDate(2016, 5, 1), QDate(2016, 5, 31));
    QCOMPARE(dataReadySpy.size(), 1);
    const auto results = dataReadySpy.takeFirst().constFirst().value<DateEventDataHash>();
    QVERIFY(compareEventDataHashes(results, expectedData));

    plugin.loadEventsForDateRange(QDate(2016, 1, 1), QDate(2016, 1, 30));
    QCOMPARE(dataReadySpy.size(), 0);
}

void PimEventsPluginTest::testEventAdded()
{
    const QStringList allData = TestDataParser::allTestData();

    FakePimDataSource source;

    PimEventsPlugin plugin(&source);
    QSignalSpy dataReadySpy(&plugin, &PimEventsPlugin::dataReady);
    QVERIFY(dataReadySpy.isValid());

    plugin.loadEventsForDateRange(QDate(2016, 5, 1), QDate(2016, 5, 31));
    QCOMPARE(dataReadySpy.size(), 0);

    for (const QString &data : allData) {
        TestDataParser parser(data, true);
        if (parser.rangeEnd() < QDate(2016, 5, 1) || parser.rangeStart() > QDate(2016, 5, 31)) {
            continue;
        }
        const KCalendarCore::Event::Ptr event = parser.incidence().dynamicCast<KCalendarCore::Event>();
        if (event) {
            source.setAkonadiIdForIncidence(event, parser.akonadiId());
            source.calendar()->addEvent(event);
            DateEventDataHash expectedData;
            for (const CalendarEvents::EventData &dt : parser.eventData()) {
                QDate d = dt.startDateTime().date();
                while (d <= dt.endDateTime().date()) {
                    expectedData.insert(d, dt);
                    d = d.addDays(1);
                }
            }

            QCOMPARE(dataReadySpy.size(), 1);
            const auto results = dataReadySpy.takeFirst().first().value<DateEventDataHash>();
            QVERIFY(compareEventDataHashes(results, expectedData));
        }
    }
}

void PimEventsPluginTest::testEventModified()
{
    FakePimDataSource source;

    PimEventsPlugin plugin(&source);
    QSignalSpy eventModifiedSpy(&plugin, &PimEventsPlugin::eventModified);
    QVERIFY(eventModifiedSpy.isValid());

    // Populate model
    const auto allData = populateCalendar(&source, true);

    // We don't care about the result of this, we just need to have mStart and
    // mEnd set
    plugin.loadEventsForDateRange(QDate(2016, 5, 1), QDate(2016, 5, 31));

    // Non-recurring event
    {
        QVERIFY(eventModifiedSpy.isEmpty());
        KCalendarCore::Event::Ptr event = source.calendar()->event(QStringLiteral("4d7fdd2c-2d3a-4ecf-8964-00eb92225209"));
        QVERIFY(event);
        const auto expectedData = findEventData(event, allData);
        QCOMPARE(expectedData.size(), 1);
        event->setSummary(QStringLiteral("TEST"));

        QVERIFY(source.calendar()->addEvent(event));

        QCOMPARE(eventModifiedSpy.size(), 1);
        const auto result = eventModifiedSpy.takeFirst().constFirst().value<CalendarEvents::EventData>();
        // TODO: Test for other property changes too?
        QCOMPARE(result.title(), event->summary());
        QCOMPARE(result.uid(), expectedData[0].uid());
    }

    // Recurring event
    {
        QVERIFY(eventModifiedSpy.isEmpty());
        KCalendarCore::Event::Ptr event = source.calendar()->event(QStringLiteral("69971015-fe9c-4800-a20e-d46bafa24e41"));
        QVERIFY(event);
        auto expectedData = findEventData(event, allData);
        event->setSummary(QStringLiteral("TEST2"));
        QVERIFY(source.calendar()->addEvent(event));

        QCOMPARE(eventModifiedSpy.size(), expectedData.size());
        while (!eventModifiedSpy.isEmpty()) {
            const auto args = eventModifiedSpy.takeFirst();
            const auto &resultData = args[0].value<CalendarEvents::EventData>();
            const auto expected = std::find_if(expectedData.begin(), expectedData.end(), [resultData](const CalendarEvents::EventData &e) {
                return e.uid() == resultData.uid();
            });
            QVERIFY(expected != expectedData.end());
            expectedData.erase(expected);
            QCOMPARE(resultData.title(), QString::fromLatin1("TEST2"));
        }
        QVERIFY(expectedData.isEmpty());
    }
}

void PimEventsPluginTest::testEventRemoved()
{
    FakePimDataSource source;

    PimEventsPlugin plugin(&source);
    QSignalSpy eventRemovedSpy(&plugin, &PimEventsPlugin::eventRemoved);
    QVERIFY(eventRemovedSpy.isValid());

    const auto allData = populateCalendar(&source, true);

    // We don't care about the result of this, we just need to have mStart and
    // mEnd set
    plugin.loadEventsForDateRange(QDate(2016, 5, 1), QDate(2016, 5, 31));

    // Non-recurring event
    {
        QVERIFY(eventRemovedSpy.isEmpty());
        const KCalendarCore::Event::Ptr event = source.calendar()->event(QStringLiteral("4d7fdd2c-2d3a-4ecf-8964-00eb92225209"));
        QVERIFY(event);
        const auto expectedData = findEventData(event, allData);
        QCOMPARE(expectedData.size(), 1);

        QVERIFY(source.calendar()->deleteEvent(event));

        QCOMPARE(eventRemovedSpy.size(), 1);
        const auto result = eventRemovedSpy.takeFirst().first().toString();
        QCOMPARE(result, expectedData[0].uid());
    }

    // Recurring event
    {
        QVERIFY(eventRemovedSpy.isEmpty());
        KCalendarCore::Event::Ptr event = source.calendar()->event(QStringLiteral("69971015-fe9c-4800-a20e-d46bafa24e41"));
        QVERIFY(event);
        auto expectedData = findEventData(event, allData);

        QVERIFY(source.calendar()->deleteEvent(event));

        QCOMPARE(eventRemovedSpy.size(), expectedData.size());
        while (!eventRemovedSpy.isEmpty()) {
            const QString resultUid = eventRemovedSpy.takeFirst().first().toString();
            const auto expected = std::find_if(expectedData.begin(), expectedData.end(), [resultUid](const CalendarEvents::EventData &e) {
                return e.uid() == resultUid;
            });
            QVERIFY(expected != expectedData.end());
            expectedData.erase(expected);
        }
        QVERIFY(expectedData.isEmpty());
    }
}

QTEST_MAIN(PimEventsPluginTest)
