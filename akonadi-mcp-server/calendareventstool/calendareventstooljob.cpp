/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "calendareventstooljob.h"
#include "calendarcommon/calendartoolutils.h"
#include <KCalendarCore/Event>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

namespace
{
constexpr int maximumEntries = 200;
}

CalendarEventsToolJob::CalendarEventsToolJob(QObject *parent)
    : CalendarToolJobBase{parent}
{
}

CalendarEventsToolJob::~CalendarEventsToolJob() = default;

void CalendarEventsToolJob::setStart(const QDateTime &start)
{
    mStart = start;
}

void CalendarEventsToolJob::setEnd(const QDateTime &end)
{
    mEnd = end;
}

bool CalendarEventsToolJob::canStart() const
{
    return CalendarToolJobBase::canStart() && mStart.isValid() && mEnd > mStart;
}

QStringList CalendarEventsToolJob::mimeTypes() const
{
    return {KCalendarCore::Event::eventMimeType()};
}

QString CalendarEventsToolJob::generateResult(const KCalendarCore::Calendar::Ptr &calendar) const
{
    const QList<CalendarToolUtils::Occurrence> occurrences = CalendarToolUtils::occurrences(calendar, mStart, mEnd);
    if (occurrences.isEmpty()) {
        return i18n("No event between %1 and %2", CalendarToolUtils::formatDateTime(mStart), CalendarToolUtils::formatDateTime(mEnd));
    }
    QStringList entries;
    entries.reserve(std::min<qsizetype>(occurrences.count(), maximumEntries) + 1);
    for (const CalendarToolUtils::Occurrence &occurrence : occurrences) {
        if (entries.count() == maximumEntries) {
            entries.append(u"... and %1 more events"_s.arg(occurrences.count() - maximumEntries));
            break;
        }
        entries.append(CalendarToolUtils::formatOccurrence(occurrence));
    }
    return entries.join(u'\n');
}
