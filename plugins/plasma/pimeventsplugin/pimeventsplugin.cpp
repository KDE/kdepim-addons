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
#include "akonadipimdatasource.h"
#include "pimeventsplugin_debug.h"

PimEventsPlugin::PimEventsPlugin(QObject *parent)
    : PimEventsPlugin(new AkonadiPimDataSource(), parent)
{
    static_cast<AkonadiPimDataSource *>(mDataSource)->setParent(this);
}

PimEventsPlugin::PimEventsPlugin(PimDataSource *dataSource, QObject *parent)
    : CalendarEvents::CalendarEventsPlugin(parent)
    , mDataSource(dataSource)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "PIM Events Plugin activated";

    dataSource->calendar()->registerObserver(this);
}

PimEventsPlugin::~PimEventsPlugin()
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "PIM Events Plugin deactivated";
}

void PimEventsPlugin::loadEventsForDateRange(const QDate &startDate, const QDate &endDate)
{
    mStart = startDate;
    mEnd = endDate;

    int eventsCount = 0, eventDataCount = 0;
    {
        EventDataVisitor visitor(mDataSource, startDate, endDate);
        const KCalCore::Event::List events = mDataSource->calendar()->events(startDate, endDate);
        eventsCount = events.count();
        if (visitor.act(events)) {
            eventDataCount = visitor.results().count();
            Q_EMIT dataReady(visitor.results());
        }
    }

    int todosCount = 0, todoDataCount = 0;
    {
        EventDataVisitor visitor(mDataSource, startDate, endDate);
        const KCalCore::Todo::List todos = mDataSource->calendar()->todos(startDate, endDate);
        todosCount = todos.count();
        if (visitor.act(todos)) {
            todoDataCount = visitor.results().count();
            Q_EMIT dataReady(visitor.results());
        }
    }
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Range:" << startDate.toString(Qt::ISODate) << "-" << endDate.toString(Qt::ISODate)
                                 << "Events:" << eventsCount
                                 << "EventData:" << eventDataCount
                                 << "Todos:" << todosCount
                                 << "TodoData:" << todoDataCount;
}

void PimEventsPlugin::calendarIncidenceAdded(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        // Don't bother with changes that happen before the applet starts populating data
        return;
    }
    EventDataVisitor visitor(mDataSource, mStart, mEnd);
    if (visitor.act(incidence)) {
        Q_EMIT dataReady(visitor.results());
    }
}

void PimEventsPlugin::calendarIncidenceChanged(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        return;
    }
    EventDataVisitor visitor(mDataSource, mStart, mEnd);
    if (visitor.act(incidence)) {
        for (const auto &ed : visitor.results()) {
            Q_EMIT eventModified(ed);
        }
    }
}

void PimEventsPlugin::calendarIncidenceAboutToBeDeleted(const KCalCore::Incidence::Ptr &incidence)
{
    if (!mStart.isValid() || !mEnd.isValid()) {
        return;
    }
    EventDataIdVisitor visitor(mDataSource, mStart, mEnd);
    if (visitor.act(incidence)) {
        for (const QString &uid : visitor.results()) {
            Q_EMIT eventRemoved(uid);
        }
    }
}
