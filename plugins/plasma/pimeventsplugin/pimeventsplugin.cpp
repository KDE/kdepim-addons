/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "pimeventsplugin.h"
#include "akonadipimdatasource.h"
#include "eventdatavisitor.h"
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

    int eventsCount = 0;
    int eventDataCount = 0;
    {
        EventDataVisitor visitor(mDataSource, startDate, endDate);
        const KCalendarCore::Event::List events = mDataSource->calendar()->events(startDate, endDate);
        eventsCount = events.count();
        if (visitor.act(events)) {
            eventDataCount = visitor.results().count();
            Q_EMIT dataReady(visitor.results());
        }
    }

    int todosCount = 0;
    int todoDataCount = 0;
    {
        EventDataVisitor visitor(mDataSource, startDate, endDate);
        const KCalendarCore::Todo::List todos = mDataSource->calendar()->todos(startDate, endDate);
        todosCount = todos.count();
        if (visitor.act(todos)) {
            todoDataCount = visitor.results().count();
            Q_EMIT dataReady(visitor.results());
        }
    }
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Range:" << startDate.toString(Qt::ISODate) << "-" << endDate.toString(Qt::ISODate) << "Events:" << eventsCount
                                 << "EventData:" << eventDataCount << "Todos:" << todosCount << "TodoData:" << todoDataCount;
}

void PimEventsPlugin::calendarIncidenceAdded(const KCalendarCore::Incidence::Ptr &incidence)
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

void PimEventsPlugin::calendarIncidenceChanged(const KCalendarCore::Incidence::Ptr &incidence)
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

void PimEventsPlugin::calendarIncidenceAboutToBeDeleted(const KCalendarCore::Incidence::Ptr &incidence)
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

#include "moc_pimeventsplugin.cpp"
