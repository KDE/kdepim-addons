/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "testdataparser.h"
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimeZone>

#include <QTest>

#include <KCalendarCore/ICalFormat>
#include <KCalendarCore/MemoryCalendar>

#include <CalendarEvents/CalendarEventsPlugin>

TestDataParser::TestDataParser(const QString &testData, bool uniqueEventData)
    : mTestData(testData)
    , mUniqueEventData(uniqueEventData)
{
    parse();
}

TestDataParser::~TestDataParser() = default;

QStringList TestDataParser::allTestData()
{
    QDir testdir(QStringLiteral(PIMEVENT_DATADIR "/data"));
    const auto data = testdir.entryInfoList({QStringLiteral("*.json")}, QDir::Files);
    QStringList testcases;
    testcases.reserve(data.count());
    for (const auto &fi : data) {
        testcases << fi.baseName();
    }
    return testcases;
}

QDate TestDataParser::rangeStart() const
{
    return mRangeStart;
}

QDate TestDataParser::rangeEnd() const
{
    return mRangeEnd;
}

qint64 TestDataParser::akonadiId() const
{
    return mAkonadiId;
}

QList<CalendarEvents::EventData> TestDataParser::eventData() const
{
    return mEventData;
}

KCalendarCore::Incidence::Ptr TestDataParser::incidence() const
{
    return mIncidence;
}

QDateTime TestDataParser::parseDateTime(const QJsonObject &dateTime)
{
    const auto date = QDate::fromString(dateTime[QStringLiteral("date")].toString(), Qt::ISODate);
    const auto time = QTime::fromString(dateTime[QStringLiteral("time")].toString(), Qt::ISODate);
    if (dateTime.contains(QLatin1StringView("tz"))) {
        return QDateTime(date, time, QTimeZone(dateTime[QStringLiteral("tz")].toString().toLatin1())).toLocalTime();
    } else {
        return QDateTime(date, time, Qt::LocalTime);
    }
}

void TestDataParser::parse()
{
    QFile icalFile(QStringLiteral(PIMEVENT_DATADIR "/data/%1.ics").arg(mTestData));
    QVERIFY(icalFile.exists());
    QVERIFY(icalFile.open(QIODevice::ReadOnly));

    auto calendar = KCalendarCore::MemoryCalendar::Ptr::create(QTimeZone::systemTimeZone());
    KCalendarCore::ICalFormat format;
    QVERIFY(format.load(calendar, icalFile.fileName()));
    QVERIFY(!calendar->incidences().isEmpty());
    mIncidence = calendar->incidences().at(0);
    QVERIFY(mIncidence);

    QFile jsonFile(QStringLiteral(PIMEVENT_DATADIR "/data/%1.json").arg(mTestData));
    QVERIFY(jsonFile.exists());
    QVERIFY(jsonFile.open(QIODevice::ReadOnly));

    const QByteArray json = jsonFile.readAll();
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(json);
    const QJsonObject doc = jsonDoc.object();
    mRangeStart = QDate::fromString(doc[QStringLiteral("rangeStart")].toString(), Qt::ISODate);
    mRangeEnd = QDate::fromString(doc[QStringLiteral("rangeEnd")].toString(), Qt::ISODate);
    mAkonadiId = doc[QStringLiteral("akonadiId")].toInt();

    const QJsonArray array = doc[QStringLiteral("eventData")].toArray();
    for (auto iter = array.constBegin(), end = array.constEnd(); iter != end; ++iter) {
        CalendarEvents::EventData eventData;
        const QJsonObject obj = iter->toObject();
        eventData.setTitle(obj[QStringLiteral("summary")].toString());
        eventData.setDescription(obj[QStringLiteral("description")].toString());
        const QString type = obj[QStringLiteral("type")].toString();
        if (type == QLatin1StringView("Event")) {
            eventData.setEventType(CalendarEvents::EventData::Event);
        } else {
            eventData.setEventType(CalendarEvents::EventData::Todo);
        }
        eventData.setIsAllDay(obj[QStringLiteral("allDay")].toBool());
        eventData.setIsMinor(obj[QStringLiteral("isMinor")].toBool());
        QDateTime startDateTime = parseDateTime(obj[QStringLiteral("startDateTime")].toObject());
        if (eventData.isAllDay()) {
            startDateTime.setTime(QTime(0, 0, 0, Qt::LocalTime));
        }
        eventData.setStartDateTime(startDateTime);
        QDateTime endDateTime = parseDateTime(obj[QStringLiteral("endDateTime")].toObject());
        if (eventData.isAllDay()) {
            endDateTime.setTime(QTime(0, 0, 0, Qt::LocalTime));
        }
        eventData.setEndDateTime(endDateTime);
        eventData.setUid(obj[QStringLiteral("uid")].toString());

        if (mUniqueEventData) {
            mEventData.push_back(eventData);
        } else {
            QDate d = startDateTime.date();
            const QDate dateEnd = endDateTime.date();
            while (d <= dateEnd) {
                mEventData.push_back(eventData);
                d = d.addDays(1);
            }
        }
    }
    QVERIFY(!mEventData.isEmpty());
}
