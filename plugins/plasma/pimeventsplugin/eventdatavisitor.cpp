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

#include "eventdatavisitor.h"
#include "pimeventsplugin_debug.h"

#include <Akonadi/Calendar/ETMCalendar>

BaseEventDataVisitor::BaseEventDataVisitor(Akonadi::ETMCalendar *calendar,
                                           const QDate &start, const QDate &end)
    : mCalendar(calendar)
    , mStart(start)
    , mEnd(end)
{
}

BaseEventDataVisitor::~BaseEventDataVisitor()
{
}

bool BaseEventDataVisitor::act(const KCalCore::Incidence::Ptr &incidence)
{
    return incidence->accept(*this, incidence);
}

bool BaseEventDataVisitor::act(const KCalCore::Event::List &events)
{
    bool ok = false;
    Q_FOREACH (const KCalCore::Event::Ptr &event, events) {
        ok = event.staticCast<KCalCore::IncidenceBase>()->accept(*this, event) || ok;
    }
    return ok;
}
bool BaseEventDataVisitor::act(const KCalCore::Todo::List &todos)
{
    bool ok = false;
    Q_FOREACH (const KCalCore::Todo::Ptr &todo, todos) {
        ok = todo.staticCast<KCalCore::IncidenceBase>()->accept(*this, todo) || ok;
    }
    return ok;
}

bool BaseEventDataVisitor::isInRange(const QDate &start, const QDate &end) const
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        return true;
    }

    if (!end.isValid() && start >= mStart && start <= mEnd) {
        return true;
    } else if (start < mStart) {
        return end >= mStart;
    } else if (end > mEnd) {
        return start <= mEnd;
    } else {
        return true;
    }
}

QString BaseEventDataVisitor::generateUid(const KCalCore::Incidence::Ptr &incidence,
                                          const KDateTime &recurrenceId) const
{
    // Get a corresponding Akonadi Item: Akonadi ID is the only reliably unique
    // and persistent identifier when dealing with incidences from multiple
    // calendars
    const Akonadi::Item item = mCalendar->item(incidence);
    if (!item.isValid()) {
        // Can this happen? What do we do now?!
        return QString();
    }

    if (recurrenceId.isValid()) {
        return QStringLiteral("Akonadi-%1-%2").arg(item.id())
                                              .arg(recurrenceId.toString(QStringLiteral("%Y%m%dT%H%M%S%Z")));
    } else {
        return QStringLiteral("Akonadi-%1").arg(item.id());
    }
}



EventDataVisitor::EventDataVisitor(Akonadi::ETMCalendar *calendar,
                                   const QDate &start, const QDate &end)
    : BaseEventDataVisitor(calendar, start , end)
{
}

EventDataVisitor::~EventDataVisitor()
{
}


QMultiHash<QDate, CalendarEvents::EventData> EventDataVisitor::results() const
{
    return mResults;
}


bool EventDataVisitor::visit(const KCalCore::Event::Ptr &event)
{
    CalendarEvents::EventData data = incidenceData(event);
    data.setEventType(CalendarEvents::EventData::Event);
    if (event->recurs()) {
        return explodeIncidenceOccurences(data, event);
    } else if (isInRange(event->dtStart().date(), event->dtEnd().date())) {
        data.setStartDateTime(event->dtStart().dateTime());
        data.setEndDateTime(event->dtEnd().dateTime());
        mResults.insert(data.startDateTime().date(), data);
        return true;
    }

    return false;
}

bool EventDataVisitor::visit(const KCalCore::Todo::Ptr &todo)
{
    CalendarEvents::EventData data = incidenceData(todo);
    data.setEventType(CalendarEvents::EventData::Todo);
    if (todo->recurs()) {
        return explodeIncidenceOccurences(data, todo);
    } else if (isInRange(todo->dtStart().date(), todo->dtDue().date())) {
        data.setStartDateTime(todo->dtStart().dateTime());
        data.setEndDateTime(todo->dtDue().dateTime());
        mResults.insert(data.startDateTime().date(), data);
        return true;
    }

    return false;
}

CalendarEvents::EventData EventDataVisitor::incidenceData(const KCalCore::Incidence::Ptr &incidence) const
{
    CalendarEvents::EventData data;
    data.setTitle(incidence->summary());
    data.setDescription(incidence->description());
    data.setIsAllDay(incidence->allDay());
    data.setIsMinor(false);
    data.setUid(generateUid(incidence));
    // TODO: Set calendar color
    return data;
}

bool EventDataVisitor::explodeIncidenceOccurences(const CalendarEvents::EventData &ed,
                                                  const KCalCore::Incidence::Ptr &incidence)
{
    Q_ASSERT(incidence->recurs());

    const qint64 duration = ed.startDateTime().secsTo(ed.endDateTime());

    KDateTime rec(mStart.addDays(-1), QTime(0, 0, 0));
    rec = incidence->recurrence()->getNextDateTime(rec);
    while (rec.isValid() && rec.date() <= mEnd) {
        CalendarEvents::EventData copy = ed;
        const QDateTime dt = rec.dateTime();
        copy.setStartDateTime(dt);
        // TODO: Is there a better way to find when an instance ends without
        // going through the expensive lookup in Incidence::instance(uid, recurrenceId)?
        copy.setEndDateTime(dt.addSecs(duration));
        copy.setUid(generateUid(incidence, rec));
        mResults.insert(dt.date(), copy);

        rec = incidence->recurrence()->getNextDateTime(rec);
    }

    return true;
}


EventDataIdVisitor::EventDataIdVisitor(Akonadi::ETMCalendar *calendar, const QDate &start, const QDate &end)
    : BaseEventDataVisitor(calendar, start, end)
{
}

QStringList EventDataIdVisitor::results() const
{
    return mResults;
}

bool EventDataIdVisitor::visit(const KCalCore::Event::Ptr &event)
{
    mResults.push_back(generateUid(event, event->recurrenceId()));
    return true;
}

bool EventDataIdVisitor::visit(const KCalCore::Todo::Ptr &todo)
{
    mResults.push_back(generateUid(todo, todo->recurrenceId()));
    return true;
}


