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
#include "pimdatasource.h"
#include "pimeventsplugin_debug.h"

BaseEventDataVisitor::BaseEventDataVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end)
    : mDataSource(dataSource)
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
    for (const KCalCore::Event::Ptr &event : events) {
        ok = event.staticCast<KCalCore::IncidenceBase>()->accept(*this, event) || ok;
    }
    return ok;
}

bool BaseEventDataVisitor::act(const KCalCore::Todo::List &todos)
{
    bool ok = false;
    for (const KCalCore::Todo::Ptr &todo : todos) {
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

QString BaseEventDataVisitor::generateUid(const KCalCore::Incidence::Ptr &incidence, const KDateTime &recurrenceId) const
{
    // Get a corresponding Akonadi Item: Akonadi ID is the only reliably unique
    // and persistent identifier when dealing with incidences from multiple
    // calendars
    const qint64 itemId = mDataSource->akonadiIdForIncidence(incidence);
    if (itemId <= 0) {
        // Can this happen? What do we do now?!
        return QString();
    }

    if (recurrenceId.isValid()) {
        return QStringLiteral("Akonadi-%1-%2").arg(itemId)
               .arg(recurrenceId.toString(QStringLiteral("%Y%m%dT%H%M%S%Z")));
    } else {
        return QStringLiteral("Akonadi-%1").arg(itemId);
    }
}

QVector<CalendarEvents::EventData> BaseEventDataVisitor::explodeIncidenceOccurences(const CalendarEvents::EventData &ed, const KCalCore::Incidence::Ptr &incidence, bool &ok)
{
    Q_ASSERT(incidence->recurs());

    const qint64 duration = ed.startDateTime().secsTo(ed.endDateTime());

    KDateTime rec(mStart.addDays(-1), QTime(0, 0, 0));
    rec = incidence->recurrence()->getNextDateTime(rec);
    QVector<CalendarEvents::EventData> results;
    while (rec.isValid() && rec.date() <= mEnd) {
        CalendarEvents::EventData copy = ed;
        QDateTime dt;
        if (incidence->allDay()) {
            dt = QDateTime(rec.date(), QTime(0, 0, 0), Qt::LocalTime);
        } else {
            dt = rec.toLocalZone().dateTime();
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

EventDataVisitor::~EventDataVisitor()
{
}

const QMultiHash<QDate, CalendarEvents::EventData> &EventDataVisitor::results() const
{
    return mResults;
}

bool EventDataVisitor::visit(const KCalCore::Incidence::Ptr &incidence, CalendarEvents::EventData::EventType type)
{
    CalendarEvents::EventData data = incidenceData(incidence);
    data.setEventType(type);
    if (incidence->recurs()) {
        bool ok = false;
        const auto list = explodeIncidenceOccurences(data, incidence, ok);
        if (ok) {
            for (const auto &data : list) {
                insertResult(data);
            }
        }
        return ok;
    } else if (isInRange(data.startDateTime().date(), data.endDateTime().date())) {
        insertResult(data);
        return true;
    }

    return false;
}

bool EventDataVisitor::visit(const KCalCore::Event::Ptr &event)
{
    return visit(event, CalendarEvents::EventData::Event);
}

bool EventDataVisitor::visit(const KCalCore::Todo::Ptr &todo)
{
    return visit(todo, CalendarEvents::EventData::Todo);
}

void EventDataVisitor::insertResult(const CalendarEvents::EventData &result)
{
    QDate d = result.startDateTime().date();
    const QDate end = result.endDateTime().date();
    while (d <= end) {
        mResults.insert(d, result);
        d = d.addDays(1);
    }
}

CalendarEvents::EventData EventDataVisitor::incidenceData(const KCalCore::Incidence::Ptr &incidence) const
{
    CalendarEvents::EventData data;
    data.setTitle(incidence->summary());
    data.setDescription(incidence->description());
    data.setIsAllDay(incidence->allDay());
    data.setIsMinor(false);
    data.setUid(generateUid(incidence));
    data.setStartDateTime(incidence->dtStart().toLocalZone().dateTime());
    data.setEndDateTime(incidence->dateTime(KCalCore::Incidence::RoleEnd).toLocalZone().dateTime());
    data.setEventColor(mDataSource->calendarColorForIncidence(incidence));
    return data;
}

EventDataIdVisitor::EventDataIdVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end)
    : BaseEventDataVisitor(dataSource, start, end)
{
}

const QStringList &EventDataIdVisitor::results() const
{
    return mResults;
}

bool EventDataIdVisitor::visit(const KCalCore::Event::Ptr &event)
{
    return visit(event.staticCast<KCalCore::Incidence>());
}

bool EventDataIdVisitor::visit(const KCalCore::Todo::Ptr &todo)
{
    return visit(todo.staticCast<KCalCore::Incidence>());
}

bool EventDataIdVisitor::visit(const KCalCore::Incidence::Ptr &incidence)
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
