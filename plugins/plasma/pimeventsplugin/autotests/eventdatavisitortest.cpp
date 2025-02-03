/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "eventdatavisitortest.h"
#include "../eventdatavisitor.h"
#include "fakepimdatasource.h"
#include "testdataparser.h"
#include "testutils.h"

#include <QTest>

#include <KCalendarCore/Event>
#include <KCalendarCore/Todo>

#include <CalendarEvents/CalendarEventsPlugin>

Q_DECLARE_METATYPE(CalendarEvents::EventData)
Q_DECLARE_METATYPE(KCalendarCore::Incidence::Ptr)

template<typename Visitor>
class TestableVisitor : public Visitor
{
public:
    TestableVisitor(PimDataSource *source, QDate start = QDate(), QDate end = QDate())
        : Visitor(source, start, end)
    {
    }

    [[nodiscard]] QString callGenerateUid(const KCalendarCore::Incidence::Ptr &incidence, const QDateTime &recurrenceId) const
    {
        return Visitor::generateUid(incidence, recurrenceId);
    }

    [[nodiscard]] bool callIsInRange(QDate start, QDate end) const
    {
        return Visitor::isInRange(start, end);
    }

    QList<CalendarEvents::EventData>
    callExplodeIncidenceOccurences(const CalendarEvents::EventData &baseEd, const KCalendarCore::Incidence::Ptr &incidence, bool &ok)
    {
        return Visitor::explodeIncidenceOccurences(baseEd, incidence, ok);
    }
};

using TestableEventDataVisitor = TestableVisitor<EventDataVisitor>;
using TestableEventDataIdVisitor = TestableVisitor<EventDataIdVisitor>;

using DateTimeRange = QPair<QDateTime, QDateTime>;

void EventDataVisitorTest::initTestCase()
{
    qputenv("TZ", "Europe/Berlin");
}

void EventDataVisitorTest::testGenerateUID_data()
{
    QTest::addColumn<KCalendarCore::Incidence::Ptr>("incidence");
    QTest::addColumn<QDateTime>("recurrenceId");
    QTest::addColumn<qint64>("itemId");
    QTest::addColumn<QString>("expectedUID");

    auto incidence = KCalendarCore::Event::Ptr::create().staticCast<KCalendarCore::Incidence>();
    QTest::newRow("simple event") << incidence << QDateTime() << 1ll << QStringLiteral("Akonadi-1");
    QTest::newRow("recurring event") << incidence << QDateTime(QDate(2016, 5, 29), QTime(15, 47, 0), QTimeZone::UTC) << 1ll
                                     << QStringLiteral("Akonadi-1-20160529T154700UTC");

    incidence = KCalendarCore::Todo::Ptr::create().staticCast<KCalendarCore::Incidence>();
    QTest::newRow("simple todo") << incidence << QDateTime() << 42ll << QStringLiteral("Akonadi-42");
    QTest::newRow("recurring todo") << incidence << QDateTime(QDate(2016, 5, 29), QTime(15, 49, 5), QTimeZone::UTC) << 42ll
                                    << QStringLiteral("Akonadi-42-20160529T154905UTC");
}

void EventDataVisitorTest::testGenerateUID()
{
    QFETCH(KCalendarCore::Incidence::Ptr, incidence);
    QFETCH(QDateTime, recurrenceId);
    QFETCH(qint64, itemId);
    QFETCH(QString, expectedUID);

    FakePimDataSource source;
    source.setAkonadiIdForIncidence(incidence, itemId);
    TestableEventDataVisitor visitor(&source);

    const QString result = visitor.callGenerateUid(incidence, recurrenceId);
    QCOMPARE(result, expectedUID);
}

void EventDataVisitorTest::testIsInRange_data()
{
    QTest::addColumn<QDate>("rangeStart");
    QTest::addColumn<QDate>("rangeEnd");
    QTest::addColumn<QDate>("eventStart");
    QTest::addColumn<QDate>("eventEnd");
    QTest::addColumn<bool>("expectedResult");

    QTest::newRow("single day fully in-range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 3) << QDate(2016, 5, 3) << true;
    QTest::newRow("multiday fully in-range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 3) << QDate(2016, 5, 15) << true;
    QTest::newRow("multiday start overlap") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 4, 28) << QDate(2016, 5, 5) << true;
    QTest::newRow("multiday end overlap") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 28) << QDate(2016, 6, 5) << true;
    QTest::newRow("single day range edge start") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 1) << QDate(2016, 5, 1) << true;
    QTest::newRow("single day range edge end") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 31) << QDate(2016, 5, 31) << true;
    QTest::newRow("multiday range edge start") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 1) << QDate(2016, 5, 10) << true;
    QTest::newRow("multiday range edge end") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 5, 20) << QDate(2016, 5, 31) << true;
    QTest::newRow("single day before range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 4, 28) << QDate(2016, 4, 28) << false;
    QTest::newRow("single day after range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 6, 4) << QDate(2016, 6, 4) << false;
    QTest::newRow("multiday before range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 4, 12) << QDate(2016, 4, 20) << false;
    QTest::newRow("multiday after range") << QDate(2016, 5, 1) << QDate(2016, 5, 31) << QDate(2016, 6, 5) << QDate(2016, 6, 10) << false;
}

void EventDataVisitorTest::testIsInRange()
{
    QFETCH(QDate, rangeStart);
    QFETCH(QDate, rangeEnd);
    QFETCH(QDate, eventStart);
    QFETCH(QDate, eventEnd);
    QFETCH(bool, expectedResult);

    FakePimDataSource source;
    TestableEventDataVisitor visitor(&source, rangeStart, rangeEnd);
    const bool result = visitor.callIsInRange(eventStart, eventEnd);
    QCOMPARE(result, expectedResult);
}

void EventDataVisitorTest::testExplodeIncidenceOccurences_data()
{
    QTest::addColumn<QDate>("rangeStart");
    QTest::addColumn<QDate>("rangeEnd");
    QTest::addColumn<CalendarEvents::EventData>("baseEventData");
    QTest::addColumn<KCalendarCore::Incidence::Ptr>("incidence");
    QTest::addColumn<qint64>("akonadiItemId");
    QTest::addColumn<QList<CalendarEvents::EventData>>("expectedEventData");

    const auto allTestData = TestDataParser::allTestData();
    for (const auto &testData : allTestData) {
        TestDataParser parser(testData, true);
        // skip non-recurring testcases
        if (!parser.incidence()->recurs()) {
            continue;
        }
        QTest::newRow(qPrintable(testData)) << parser.rangeStart() << parser.rangeEnd() << parser.eventData().constFirst() << parser.incidence()
                                            << parser.akonadiId() << parser.eventData();
    }
}

void EventDataVisitorTest::testExplodeIncidenceOccurences()
{
    QFETCH(QDate, rangeStart);
    QFETCH(QDate, rangeEnd);
    QFETCH(CalendarEvents::EventData, baseEventData);
    QFETCH(KCalendarCore::Incidence::Ptr, incidence);
    QFETCH(qint64, akonadiItemId);
    QFETCH(QList<CalendarEvents::EventData>, expectedEventData);

    FakePimDataSource source;
    source.setAkonadiIdForIncidence(incidence, akonadiItemId);
    TestableEventDataVisitor visitor(&source, rangeStart, rangeEnd);
    bool ok = false;
    const auto results = visitor.callExplodeIncidenceOccurences(baseEventData, incidence, ok);
    QVERIFY(ok);

    QCOMPARE(results.size(), expectedEventData.size());
    for (int i = 0; i < results.size(); ++i) {
        QVERIFY(TestUtils::compareEventData(results[i], expectedEventData[i]));
    }
}

void EventDataVisitorTest::testEventDataVisitor_data()
{
    QTest::addColumn<QDate>("rangeStart");
    QTest::addColumn<QDate>("rangeEnd");
    QTest::addColumn<KCalendarCore::Incidence::Ptr>("incidence");
    QTest::addColumn<qint64>("akonadiItemId");
    QTest::addColumn<QList<CalendarEvents::EventData>>("expectedResults");

    const auto allTestData = TestDataParser::allTestData();
    for (const auto &testData : allTestData) {
        TestDataParser parser(testData);

        QTest::newRow(qPrintable(testData)) << parser.rangeStart() << parser.rangeEnd() << parser.incidence() << parser.akonadiId() << parser.eventData();
    }
}

void EventDataVisitorTest::testEventDataVisitor()
{
    QFETCH(QDate, rangeStart);
    QFETCH(QDate, rangeEnd);
    QFETCH(KCalendarCore::Incidence::Ptr, incidence);
    QFETCH(qint64, akonadiItemId);
    QFETCH(QList<CalendarEvents::EventData>, expectedResults);

    FakePimDataSource source;
    source.setAkonadiIdForIncidence(incidence, akonadiItemId);
    TestableEventDataVisitor visitor(&source, rangeStart, rangeEnd);
    QVERIFY(visitor.act(incidence));

    const auto &results = visitor.results();
    QCOMPARE(results.size(), expectedResults.size());

    auto resultValues = results.values();
    std::sort(resultValues.begin(), resultValues.end(), std::less<CalendarEvents::EventData>());
    for (int i = 0; i < resultValues.size(); ++i) {
        const auto &result = resultValues[i];
        const auto &expectedResult = expectedResults[i];

        QVERIFY(TestUtils::compareEventData(result, expectedResult));
    }
}

void EventDataVisitorTest::testEventDataIdVisitor_data()
{
    QTest::addColumn<QDate>("rangeStart");
    QTest::addColumn<QDate>("rangeEnd");
    QTest::addColumn<KCalendarCore::Incidence::Ptr>("incidence");
    QTest::addColumn<qint64>("akonadiItemId");
    QTest::addColumn<QStringList>("expectedUids");

    const auto allTestData = TestDataParser::allTestData();
    for (const auto &testData : allTestData) {
        TestDataParser parser(testData, true);
        QStringList uids;
        for (const auto &ed : parser.eventData()) {
            uids.push_back(ed.uid());
        }
        QTest::newRow(qPrintable(testData)) << parser.rangeStart() << parser.rangeEnd() << parser.incidence() << parser.akonadiId() << uids;
    }
}

void EventDataVisitorTest::testEventDataIdVisitor()
{
    QFETCH(QDate, rangeStart);
    QFETCH(QDate, rangeEnd);
    QFETCH(KCalendarCore::Incidence::Ptr, incidence);
    QFETCH(qint64, akonadiItemId);
    QFETCH(QStringList, expectedUids);

    FakePimDataSource source;
    source.setAkonadiIdForIncidence(incidence, akonadiItemId);
    TestableEventDataIdVisitor visitor(&source, rangeStart, rangeEnd);
    QVERIFY(visitor.act(incidence));

    auto results = visitor.results();

    std::sort(results.begin(), results.end());
    std::sort(expectedUids.begin(), expectedUids.end());
    QCOMPARE(results, expectedUids);
}

QTEST_MAIN(EventDataVisitorTest)

#include "moc_eventdatavisitortest.cpp"
