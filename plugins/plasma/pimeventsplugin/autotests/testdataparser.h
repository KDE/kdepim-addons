/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */
#pragma once

#include <KCalendarCore/Incidence>
#include <QDate>

namespace CalendarEvents
{
class EventData;
}
class QDateTime;
class QJsonObject;

class TestDataParser
{
public:
    explicit TestDataParser(const QString &testData, bool uniqueEventData = false);
    ~TestDataParser();

    Q_REQUIRED_RESULT QDate rangeStart() const;
    Q_REQUIRED_RESULT QDate rangeEnd() const;
    Q_REQUIRED_RESULT qint64 akonadiId() const;
    Q_REQUIRED_RESULT KCalendarCore::Incidence::Ptr incidence() const;
    Q_REQUIRED_RESULT QList<CalendarEvents::EventData> eventData() const;

    Q_REQUIRED_RESULT static QStringList allTestData();

private:
    void parse();
    QDateTime parseDateTime(const QJsonObject &datetime);

    QString mTestData;
    QDate mRangeStart;
    QDate mRangeEnd;
    qint64 mAkonadiId;
    KCalendarCore::Incidence::Ptr mIncidence;
    QList<CalendarEvents::EventData> mEventData;
    bool mUniqueEventData;
};
