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

#include "pimeventsplugin.h"
#include "eventdatavisitor.h"
#include "pimeventsplugin_debug.h"

#include <Akonadi/Calendar/ETMCalendar>
#include <KCalCore/Visitor>

#define TRACE_RESULTS


QDebug operator<<(QDebug dbg, const CalendarEvents::EventData &data)
{
    dbg.nospace() << data.title() << " (UID " << data.uid() << "), "
                  << data.startDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t"))
                  << " - "
                  << data.endDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss t"));
    return dbg;
}

PimEventsPlugin::PimEventsPlugin(QObject* parent)
    : CalendarEvents::CalendarEventsPlugin(parent)
    , mCalendar(Q_NULLPTR)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "PIM Events Plugin activated";

    mCalendar = new Akonadi::ETMCalendar(this);
    // TODO: Filter out disabled calendars
    // TOOD: Only retrieve PLD:HEAD once it's supported
    mCalendar->setCollectionFilteringEnabled(false);
    mCalendar->registerObserver(this);
}

PimEventsPlugin::~PimEventsPlugin()
{
}


void PimEventsPlugin::loadEventsForDateRange(const QDate &startDate, const QDate &endDate)
{
    mStart = startDate;
    mEnd = endDate;

    qCDebug(PIMEVENTSPLUGIN_LOG) << "Requested range" << startDate << endDate;
    {
        EventDataVisitor visitor(mCalendar, startDate, endDate);
        const KCalCore::Event::List events = mCalendar->events(startDate, endDate);
        qCDebug(PIMEVENTSPLUGIN_LOG) << "\tFound" << events.count() << "events";
        if (visitor.act(events)) {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "\tGenerated" << visitor.results().count() << "EventData";
#ifdef TRACE_RESULTS
            Q_FOREACH (const auto &ed, visitor.results()) {
                qCDebug(PIMEVENTSPLUGIN_LOG) << "\t" << ed;
            }
#endif
            Q_EMIT dataReady(visitor.results());
        } else {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "\tGenerated 0 EventData";
        }
    }

    {
        EventDataVisitor visitor(mCalendar, startDate, endDate);
        const KCalCore::Todo::List todos = mCalendar->todos(startDate, endDate);
        qCDebug(PIMEVENTSPLUGIN_LOG) << "\tFound" << todos.count() << "todos";
        if (visitor.act(todos)) {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "\tGenerated" << visitor.results().count() << "EventData";
#ifdef TRACE_RESULTS
            Q_FOREACH (const auto &ed, visitor.results()) {
                qCDebug(PIMEVENTSPLUGIN_LOG) << "\t" << ed;
            }
#endif
            Q_EMIT dataReady(visitor.results());
        } else {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "\tGenerated 0 EventData";
        }
    }
}

void PimEventsPlugin::calendarIncidenceAdded(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        // Don't bother with changes that happen before the applet starts populating data
        return;
    }
    EventDataVisitor visitor(mCalendar, mStart, mEnd);
    if (visitor.act(incidence)) {
        qCDebug(PIMEVENTSPLUGIN_LOG) << "Incidence" << incidence->uid() << "added";
        Q_EMIT dataReady(visitor.results());
    }
}

void PimEventsPlugin::calendarIncidenceChanged(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        return;
    }
    EventDataVisitor visitor(mCalendar, mStart, mEnd);
    if (visitor.act(incidence)) {
        Q_FOREACH (const auto &ed, visitor.results()) {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "EventData" << ed.uid() << "updated";
            Q_EMIT eventModified(ed);
        }
    }
}

void PimEventsPlugin::calendarIncidenceAboutToBeDeleted(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        return;
    }
    EventDataIdVisitor visitor(mCalendar, mStart, mEnd);
    if (visitor.act(incidence)) {
        Q_FOREACH (const QString &uid, visitor.results()) {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "EventData" << uid << "removed";
            Q_EMIT eventRemoved(uid);
        }
    }
}
