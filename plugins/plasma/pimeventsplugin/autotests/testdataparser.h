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

    [[nodiscard]] QDate rangeStart() const;
    [[nodiscard]] QDate rangeEnd() const;
    [[nodiscard]] qint64 akonadiId() const;
    [[nodiscard]] KCalendarCore::Incidence::Ptr incidence() const;
    [[nodiscard]] QList<CalendarEvents::EventData> eventData() const;

    [[nodiscard]] static QStringList allTestData();

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
