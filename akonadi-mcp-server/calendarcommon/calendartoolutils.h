/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KCalendarCore/Calendar>
#include <KCalendarCore/Incidence>
#include <QDateTime>
#include <QList>
#include <optional>

namespace CalendarToolUtils
{
enum class DateBound : uint8_t {
    Start,
    End,
};

struct Occurrence {
    KCalendarCore::Incidence::Ptr incidence;
    QDateTime start;
    QDateTime end;
};

struct IncidenceDateTime {
    QDateTime dateTime;
    bool allDay = false;
};

// Parse an ISO 8601 date ("2026-10-14") or date-time ("2026-10-14T14:00").
// A date used as End bound includes the whole day.
[[nodiscard]] std::optional<QDateTime> parseDateTime(const QString &str, DateBound bound);
// Parse an ISO 8601 date (all day) or date-time, in the system time zone
[[nodiscard]] std::optional<IncidenceDateTime> parseIncidenceDateTime(const QString &str);
[[nodiscard]] QString formatDateTime(const QDateTime &dateTime);
[[nodiscard]] QString formatPeriod(const QDateTime &start, const QDateTime &end);
[[nodiscard]] QString formatOccurrence(const Occurrence &occurrence);
// Occurrences overlapping [start, end[, sorted by start date
[[nodiscard]] QList<Occurrence> occurrences(const KCalendarCore::Calendar::Ptr &calendar, const QDateTime &start, const QDateTime &end);
}
