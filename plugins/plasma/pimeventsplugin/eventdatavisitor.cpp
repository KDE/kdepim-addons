/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "eventdatavisitor.h"
#include "pimdatasource.h"

BaseEventDataVisitor::BaseEventDataVisitor(PimDataSource *dataSource, QDate start, QDate end)
    : mDataSource(dataSource)
    , mStart(start)
    , mEnd(end)
{
}

BaseEventDataVisitor::~BaseEventDataVisitor() = default;

bool BaseEventDataVisitor::act(const KCalendarCore::Incidence::Ptr &incidence)
{
    return incidence->accept(*this, incidence);
}

bool BaseEventDataVisitor::act(const KCalendarCore::Event::List &events)
{
    bool ok = false;
    for (const KCalendarCore::Event::Ptr &event : events) {
        ok = event.staticCast<KCalendarCore::IncidenceBase>()->accept(*this, event) || ok;
    }
    return ok;
}

bool BaseEventDataVisitor::act(const KCalendarCore::Todo::List &todos)
{
    bool ok = false;
    for (const KCalendarCore::Todo::Ptr &todo : todos) {
        ok = todo.staticCast<KCalendarCore::IncidenceBase>()->accept(*this, todo) || ok;
    }
    return ok;
}

bool BaseEventDataVisitor::isInRange(QDate start, QDate end) const
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

QString BaseEventDataVisitor::generateUid(const KCalendarCore::Incidence::Ptr &incidence, const QDateTime &recurrenceId) const
{
    // Get a corresponding Akonadi Item: Akonadi ID is the only reliably unique
    // and persistent identifier when dealing with incidences from multiple
    // calendars
    const qint64 itemId = mDataSource->akonadiIdForIncidence(incidence);
    if (itemId <= 0) {
        // Can this happen? What do we do now?!
        return {};
    }

    if (recurrenceId.isValid()) {
        return QStringLiteral("Akonadi-%1-%2").arg(itemId).arg(recurrenceId.toString(QStringLiteral("yyyyMMddThhmmsst")));
    } else {
        return QStringLiteral("Akonadi-%1").arg(itemId);
    }
}

QList<CalendarEvents::EventData>
BaseEventDataVisitor::explodeIncidenceOccurences(const CalendarEvents::EventData &ed, const KCalendarCore::Incidence::Ptr &incidence, bool &ok)
{
    Q_ASSERT(incidence->recurs());

    const qint64 duration = ed.startDateTime().secsTo(ed.endDateTime());

    QDateTime rec(mStart.addDays(-1), QTime(0, 0, 0));
    rec = incidence->recurrence()->getNextDateTime(rec);
    QList<CalendarEvents::EventData> results;
    while (rec.isValid() && rec.date() <= mEnd) {
        CalendarEvents::EventData copy = ed;
        QDateTime dt;
        if (incidence->allDay()) {
            dt = QDateTime(rec.date(), QTime(0, 0, 0), Qt::LocalTime);
        } else {
            dt = rec.toLocalTime();
        }
        copy.setStartDateTime(dt);
        copy.setEndDateTime(dt.addSecs(duration));
        copy.setUid(generateUid(incidence, rec));

        results.push_back(copy);

        rec = incidence->recurrence()->getNextDateTime(rec);
    }

    ok = true;
    return results;
}

EventDataVisitor::EventDataVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end)
    : BaseEventDataVisitor(dataSource, start, end)
{
}

EventDataVisitor::~EventDataVisitor() = default;

const QMultiHash<QDate, CalendarEvents::EventData> &EventDataVisitor::results() const
{
    return mResults;
}

bool EventDataVisitor::visit(const KCalendarCore::Incidence::Ptr &incidence, CalendarEvents::EventData::EventType type)
{
    CalendarEvents::EventData data = incidenceData(incidence);
    data.setEventType(type);
    if (incidence->recurs()) {
        bool ok = false;
        const auto list = explodeIncidenceOccurences(data, incidence, ok);
        if (ok) {
            for (const auto &dataCalendar : list) {
                insertResult(dataCalendar);
            }
        }
        return ok;
    } else if (isInRange(data.startDateTime().date(), data.endDateTime().date())) {
        insertResult(data);
        return true;
    }

    return false;
}

bool EventDataVisitor::visit(const KCalendarCore::Event::Ptr &event)
{
    return visit(event, CalendarEvents::EventData::Event);
}

bool EventDataVisitor::visit(const KCalendarCore::Todo::Ptr &todo)
{
    return visit(todo, CalendarEvents::EventData::Todo);
}

void EventDataVisitor::insertResult(const CalendarEvents::EventData &result)
{
    QDate d = result.startDateTime().date();
    const QDate end = result.endDateTime().date();

    // Agenda without start date will be placed at the end (due) date
    if (!d.isValid()) {
        mResults.insert(end, result);
        return;
    }

    while (d <= end) {
        mResults.insert(d, result);
        d = d.addDays(1);
    }
}

CalendarEvents::EventData EventDataVisitor::incidenceData(const KCalendarCore::Incidence::Ptr &incidence) const
{
    CalendarEvents::EventData data;
    data.setTitle(incidence->summary());
    data.setDescription(incidence->description());
    data.setIsAllDay(incidence->allDay());
    data.setIsMinor(false);
    data.setUid(generateUid(incidence));
    data.setStartDateTime(incidence->dtStart().toLocalTime());
    data.setEndDateTime(incidence->dateTime(KCalendarCore::Incidence::RoleEnd).toLocalTime());
    data.setEventColor(mDataSource->calendarColorForIncidence(incidence));
    return data;
}

EventDataIdVisitor::EventDataIdVisitor(PimDataSource *dataSource, QDate start, QDate end)
    : BaseEventDataVisitor(dataSource, start, end)
{
}

const QStringList &EventDataIdVisitor::results() const
{
    return mResults;
}

bool EventDataIdVisitor::visit(const KCalendarCore::Event::Ptr &event)
{
    return visit(event.staticCast<KCalendarCore::Incidence>());
}

bool EventDataIdVisitor::visit(const KCalendarCore::Todo::Ptr &todo)
{
    return visit(todo.staticCast<KCalendarCore::Incidence>());
}

bool EventDataIdVisitor::visit(const KCalendarCore::Incidence::Ptr &incidence)
{
    if (incidence->recurs()) {
        CalendarEvents::EventData ed;
        bool ok = false;
        const auto list = explodeIncidenceOccurences(ed, incidence, ok);
        if (ok) {
            for (const auto &data : list) {
                mResults.push_back(data.uid());
            }
        }
        return ok;
    } else {
        mResults.push_back(generateUid(incidence, incidence->recurrenceId()));
    }
    return true;
}
