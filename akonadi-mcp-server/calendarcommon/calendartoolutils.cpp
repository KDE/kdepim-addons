/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "calendartoolutils.h"
#include <KCalendarCore/OccurrenceIterator>
#include <algorithm>

using namespace Qt::Literals::StringLiterals;

namespace
{
// OccurrenceIterator only returns occurrences starting in the range: look back to find the ones which are still running
constexpr int lookbackDays = 7;
constexpr int isoDateLength = 10;
}

std::optional<QDateTime> CalendarToolUtils::parseDateTime(const QString &str, DateBound bound)
{
    const QString dateTimeStr = str.trimmed();
    if (dateTimeStr.size() == isoDateLength) {
        const QDate date = QDate::fromString(dateTimeStr, Qt::ISODate);
        if (!date.isValid()) {
            return std::nullopt;
        }
        return bound == DateBound::Start ? date.startOfDay() : date.addDays(1).startOfDay();
    }
    const QDateTime dateTime = QDateTime::fromString(dateTimeStr, Qt::ISODate);
    if (!dateTime.isValid()) {
        return std::nullopt;
    }
    return dateTime;
}

QString CalendarToolUtils::formatDateTime(const QDateTime &dateTime)
{
    return dateTime.toLocalTime().toString(u"yyyy-MM-dd HH:mm"_s);
}

QString CalendarToolUtils::formatPeriod(const QDateTime &start, const QDateTime &end)
{
    if (!end.isValid() || end == start) {
        return formatDateTime(start);
    }
    const QDateTime localStart = start.toLocalTime();
    const QDateTime localEnd = end.toLocalTime();
    if (localStart.date() == localEnd.date()) {
        return formatDateTime(start) + u" - "_s + localEnd.toString(u"HH:mm"_s);
    }
    return formatDateTime(start) + u" - "_s + formatDateTime(end);
}

QString CalendarToolUtils::formatOccurrence(const Occurrence &occurrence)
{
    QString when;
    if (occurrence.incidence->allDay()) {
        const QDate startDate = occurrence.start.date();
        // Occurrence end is exclusive
        const QDate lastDate = occurrence.end.date().addDays(-1);
        when = startDate.toString(Qt::ISODate);
        if (lastDate > startDate) {
            when += u" - "_s + lastDate.toString(Qt::ISODate);
        }
        when += u" (all day)"_s;
    } else {
        when = formatPeriod(occurrence.start, occurrence.end);
    }
    QString entry = when + u": "_s + occurrence.incidence->summary();
    if (const QString location = occurrence.incidence->location(); !location.isEmpty()) {
        entry += u" (location: %1)"_s.arg(location);
    }
    return entry;
}

QList<CalendarToolUtils::Occurrence> CalendarToolUtils::occurrences(const KCalendarCore::Calendar::Ptr &calendar, const QDateTime &start, const QDateTime &end)
{
    QList<Occurrence> result;
    KCalendarCore::OccurrenceIterator it(*calendar, start.addDays(-lookbackDays), end);
    while (it.hasNext()) {
        it.next();
        Occurrence occurrence{it.incidence(), it.occurrenceStartDate(), it.occurrenceEndDate()};
        if (occurrence.incidence->allDay()) {
            occurrence.start = occurrence.start.date().startOfDay();
            occurrence.end = (occurrence.end.isValid() ? occurrence.end.date() : occurrence.start.date()).addDays(1).startOfDay();
        } else if (!occurrence.end.isValid()) {
            occurrence.end = occurrence.start;
        }
        if (occurrence.start >= end) {
            continue;
        }
        if (occurrence.end <= start && occurrence.start < start) {
            continue;
        }
        result.append(std::move(occurrence));
    }
    std::ranges::sort(result, {}, &Occurrence::start);
    return result;
}
