/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include <KCalendarCore/Incidence>
#include <QDate>

namespace CalendarEvents {
class EventData;
}
class QDateTime;
class QJsonObject;

class TestDataParser
{
public:
    explicit TestDataParser(const QString &testData, bool uniqueEventData = false);
    ~TestDataParser();

    QDate rangeStart() const;
    QDate rangeEnd() const;
    qint64 akonadiId() const;
    KCalendarCore::Incidence::Ptr incidence() const;
    QVector<CalendarEvents::EventData> eventData() const;

    static QStringList allTestData();

private:
    void parse();
    QDateTime parseDateTime(const QJsonObject &datetime);

    QString mTestData;
    QDate mRangeStart;
    QDate mRangeEnd;
    qint64 mAkonadiId;
    KCalendarCore::Incidence::Ptr mIncidence;
    QVector<CalendarEvents::EventData> mEventData;
    bool mUniqueEventData;
};
