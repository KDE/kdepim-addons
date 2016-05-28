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
#include "settingschangenotifier.h"

#include <AkonadiCore/ChangeRecorder>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/EntityDisplayAttribute>
#include <AkonadiCore/EntityTreeModel>
#include <Akonadi/Calendar/ETMCalendar>

#include <KCalCore/Visitor>

#include <KSharedConfig>
#include <KConfigGroup>

#include <QSet>

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

    connect(SettingsChangeNotifier::self(), &SettingsChangeNotifier::settingsChanged,
            this, &PimEventsPlugin::onSettingsChanged);

    mMonitor = new Akonadi::ChangeRecorder(this);
    mMonitor->setChangeRecordingEnabled(false);
    mMonitor->itemFetchScope().fetchFullPayload(true);
    mMonitor->itemFetchScope().fetchAttribute<Akonadi::EntityDisplayAttribute>();
    onSettingsChanged();

    mCalendar = new Akonadi::ETMCalendar(mMonitor, this);
    // TOOD: Only retrieve PLD:HEAD once it's supported
    mCalendar->setCollectionFilteringEnabled(false);
    mCalendar->registerObserver(this);
}

PimEventsPlugin::~PimEventsPlugin()
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "PIM Events Plugin deactivated";
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
            Q_EMIT eventRemoved(uid);
        }
    }
}

void PimEventsPlugin::onSettingsChanged()
{
    QSet<Akonadi::Collection> currentCols;
    Q_FOREACH (const Akonadi::Collection &col, mMonitor->collectionsMonitored()) {
        currentCols.insert(col);
    }

    auto config = KSharedConfig::openConfig();
    auto group = config->group("PIMEventsPlugin");
    const QList<qint64> calendars = group.readEntry(QStringLiteral("calendars"), QList<qint64>());
    QSet<Akonadi::Collection> configuredCols;
    Q_FOREACH (qint64 colId, calendars) {
        configuredCols.insert(Akonadi::Collection(colId));
    }

    qCDebug(PIMEVENTSPLUGIN_LOG) << configuredCols << currentCols;
    Q_FOREACH (const Akonadi::Collection &col, (currentCols - configuredCols)) {
        mMonitor->setCollectionMonitored(col, false);
    }
    Q_FOREACH (const Akonadi::Collection &col, (configuredCols - currentCols)) {
        mMonitor->setCollectionMonitored(col, true);
    }

    const bool hasSelectedCols = mMonitor->collectionsMonitored().isEmpty();
    mMonitor->setMimeTypeMonitored(KCalCore::Event::eventMimeType(), hasSelectedCols);
    mMonitor->setMimeTypeMonitored(KCalCore::Todo::todoMimeType(), hasSelectedCols);
    mMonitor->setMimeTypeMonitored(KCalCore::Journal::journalMimeType(), hasSelectedCols);
}
