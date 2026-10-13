/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "freebusytooljob.h"
#include "calendarcommon/calendartoolutils.h"
#include <KCalendarCore/Event>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

namespace
{
struct BusyPeriod {
    QDateTime start;
    QDateTime end;
    QStringList summaries;
};
}

FreeBusyToolJob::FreeBusyToolJob(QObject *parent)
    : CalendarToolJobBase{parent}
{
}

FreeBusyToolJob::~FreeBusyToolJob() = default;

void FreeBusyToolJob::setStart(const QDateTime &start)
{
    mStart = start;
}

void FreeBusyToolJob::setEnd(const QDateTime &end)
{
    mEnd = end;
}

bool FreeBusyToolJob::canStart() const
{
    return CalendarToolJobBase::canStart() && mStart.isValid() && mEnd > mStart;
}

QStringList FreeBusyToolJob::mimeTypes() const
{
    return {KCalendarCore::Event::eventMimeType()};
}

QString FreeBusyToolJob::generateResult(const KCalendarCore::Calendar::Ptr &calendar) const
{
    const QList<CalendarToolUtils::Occurrence> occurrences = CalendarToolUtils::occurrences(calendar, mStart, mEnd);
    QList<BusyPeriod> busyPeriods;
    for (const CalendarToolUtils::Occurrence &occurrence : occurrences) {
        if (const auto event = occurrence.incidence.dynamicCast<KCalendarCore::Event>(); event && event->transparency() == KCalendarCore::Event::Transparent) {
            continue;
        }
        const QDateTime start = std::max(occurrence.start, mStart);
        const QDateTime end = std::min(occurrence.end, mEnd);
        if (end <= start) {
            continue;
        }
        // Occurrences are sorted by start date: only the last period can overlap
        if (!busyPeriods.isEmpty() && start <= busyPeriods.last().end) {
            BusyPeriod &period = busyPeriods.last();
            period.end = std::max(period.end, end);
            period.summaries.append(occurrence.incidence->summary());
        } else {
            busyPeriods.append({start, end, {occurrence.incidence->summary()}});
        }
    }
    if (busyPeriods.isEmpty()) {
        return i18n("Free for the whole period from %1 to %2", CalendarToolUtils::formatDateTime(mStart), CalendarToolUtils::formatDateTime(mEnd));
    }

    QStringList busyEntries;
    QStringList freeEntries;
    QDateTime freeStart = mStart;
    for (const BusyPeriod &period : std::as_const(busyPeriods)) {
        if (period.start > freeStart) {
            freeEntries.append(u"  "_s + CalendarToolUtils::formatPeriod(freeStart, period.start));
        }
        busyEntries.append(u"  %1: %2"_s.arg(CalendarToolUtils::formatPeriod(period.start, period.end), period.summaries.join(u", "_s)));
        freeStart = period.end;
    }
    if (mEnd > freeStart) {
        freeEntries.append(u"  "_s + CalendarToolUtils::formatPeriod(freeStart, mEnd));
    }

    QString result = u"Busy:\n"_s + busyEntries.join(u'\n');
    result += u"\nFree:\n"_s + (freeEntries.isEmpty() ? u"  none"_s : freeEntries.join(u'\n'));
    return result;
}
