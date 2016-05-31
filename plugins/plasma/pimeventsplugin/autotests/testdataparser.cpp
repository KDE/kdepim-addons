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

#include "testdataparser.h"
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimeZone>

#include <QtTest/QTest>

#include <KCalCore/ICalFormat>

#include <CalendarEvents/CalendarEventsPlugin>

TestDataParser::TestDataParser(const QString &testData, bool uniqueEventData)
    : mTestData(testData)
    , mUniqueEventData(uniqueEventData)
{
    parse();
}

TestDataParser::~TestDataParser()
{
}

QStringList TestDataParser::allTestData()
{
    QDir testdir(QStringLiteral(PIMEVENT_DATADIR "/data"));
    const auto data = testdir.entryInfoList({ QStringLiteral("*.json") }, QDir::Files);
    QStringList testcases;
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

QVector<CalendarEvents::EventData> TestDataParser::eventData() const
{
    return mEventData;
}

KCalCore::Incidence::Ptr TestDataParser::incidence() const
{
    return mIncidence;
}

QDateTime TestDataParser::parseDateTime(const QJsonObject &dateTime)
{
    return QDateTime(QDate::fromString(dateTime[QStringLiteral("date")].toString(), Qt::ISODate),
                     QTime::fromString(dateTime[QStringLiteral("time")].toString(), Qt::ISODate),
                     QTimeZone(dateTime[QStringLiteral("tz")].toString().toLatin1()));
}

void TestDataParser::parse()
{
    QFile icalFile(QStringLiteral(PIMEVENT_DATADIR "/data/%1.ics").arg(mTestData));
    QVERIFY(icalFile.exists());
    QVERIFY(icalFile.open(QIODevice::ReadOnly));

    const QByteArray data = icalFile.readAll();
    KCalCore::ICalFormat format;
    mIncidence = format.readIncidence(data);
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
        if (type == QLatin1String("Event")) {
            eventData.setEventType(CalendarEvents::EventData::Event);
        } else {
            eventData.setEventType(CalendarEvents::EventData::Todo);
        }
        eventData.setIsAllDay(obj[QStringLiteral("allDay")].toBool());
        eventData.setIsMinor(obj[QStringLiteral("isMinor")].toBool());
        const QDateTime startDateTime = parseDateTime(obj[QStringLiteral("startDateTime")].toObject());
        eventData.setStartDateTime(startDateTime);
        const QDateTime endDateTime = parseDateTime(obj[QStringLiteral("endDateTime")].toObject());
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
