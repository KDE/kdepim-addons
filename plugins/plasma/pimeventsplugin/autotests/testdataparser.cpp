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
using namespace Qt::Literals::StringLiterals;

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
    const auto data = testdir.entryInfoList({u"*.json"_s}, QDir::Files);
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
    const auto date = QDate::fromString(dateTime[u"date"_s].toString(), Qt::ISODate);
    const auto time = QTime::fromString(dateTime[u"time"_s].toString(), Qt::ISODate);
    if (dateTime.contains("tz"_L1)) {
        return QDateTime(date, time, QTimeZone(dateTime[u"tz"_s].toString().toLatin1())).toLocalTime();
    } else {
        return QDateTime(date, time, QTimeZone::LocalTime);
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
    mRangeStart = QDate::fromString(doc[u"rangeStart"_s].toString(), Qt::ISODate);
    mRangeEnd = QDate::fromString(doc[u"rangeEnd"_s].toString(), Qt::ISODate);
    mAkonadiId = doc[u"akonadiId"_s].toInt();

    const QJsonArray array = doc[u"eventData"_s].toArray();
    for (auto iter = array.constBegin(), end = array.constEnd(); iter != end; ++iter) {
        CalendarEvents::EventData eventData;
        const QJsonObject obj = iter->toObject();
        eventData.setTitle(obj[u"summary"_s].toString());
        eventData.setDescription(obj[u"description"_s].toString());
        const QString type = obj[u"type"_s].toString();
        if (type == "Event"_L1) {
            eventData.setEventType(CalendarEvents::EventData::Event);
        } else {
            eventData.setEventType(CalendarEvents::EventData::Todo);
        }
        eventData.setIsAllDay(obj[u"allDay"_s].toBool());
        eventData.setIsMinor(obj[u"isMinor"_s].toBool());
        QDateTime startDateTime = parseDateTime(obj[u"startDateTime"_s].toObject());
        if (eventData.isAllDay()) {
            startDateTime.setTime(QTime(0, 0, 0, Qt::LocalTime));
        }
        eventData.setStartDateTime(startDateTime);
        QDateTime endDateTime = parseDateTime(obj[u"endDateTime"_s].toObject());
        if (eventData.isAllDay()) {
            endDateTime.setTime(QTime(0, 0, 0, Qt::LocalTime));
        }
        eventData.setEndDateTime(endDateTime);
        eventData.setUid(obj[u"uid"_s].toString());

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
