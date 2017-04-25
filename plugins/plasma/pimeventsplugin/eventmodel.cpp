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

#include "eventmodel.h"
#include "pimeventsplugin_debug.h"

#include <Akonadi/Calendar/IncidenceChanger>

#include <AkonadiCore/Monitor>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/CollectionFetchScope>
#include <AkonadiCore/EntityDisplayAttribute>
#include <AkonadiCore/CollectionColorAttribute>
#include <AkonadiCore/AttributeFactory>
#include <AkonadiCore/ItemFetchJob>

EventModel::EventModel(QObject *parent)
    : Akonadi::CalendarBase(parent)
    , mMonitor(nullptr)
{
    Akonadi::AttributeFactory::registerAttribute<Akonadi::CollectionColorAttribute>();
}

EventModel::~EventModel()
{
}

void EventModel::createMonitor()
{
    if (mMonitor) {
        return;
    }

    mMonitor = new Akonadi::Monitor(this);
    mMonitor->itemFetchScope().fetchFullPayload(true);
    mMonitor->collectionFetchScope().fetchAttribute<Akonadi::EntityDisplayAttribute>();
    mMonitor->collectionFetchScope().fetchAttribute<Akonadi::CollectionColorAttribute>();
    mMonitor->fetchCollection(true);

    connect(mMonitor, &Akonadi::Monitor::itemAdded,
            this, [this](const Akonadi::Item &item) {
        // This is super-ugly, but the only way how to insert into CalendarBase
        // without having direct access to CalendarBasePrivate.
        // changeId is luckily ignored by CalendarBase.
        incidenceChanger()->createFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
    });
    connect(mMonitor, &Akonadi::Monitor::itemChanged,
            this, [this](const Akonadi::Item &item) {
        KCalCore::Incidence::Ptr incidence;
        try {
            incidence = item.payload<KCalCore::Incidence::Ptr>();
        } catch (const Akonadi::PayloadException &e) {
            qCWarning(PIMEVENTSPLUGIN_LOG) << "Item" << item.id() << "has no payload:" << e.what();
        }
        if (!incidence) {
            return;         // HUH?!
        }
        const KCalCore::Incidence::Ptr oldIncidence = this->incidence(incidence->instanceIdentifier());
        if (!oldIncidence) {
            // Change for event we don't know about -> discard
            return;
        }

        // Unfortunately the plasma applet does not handle event moves
        // so we have to simulate via remove+add
        if (oldIncidence->allDay() != incidence->allDay()
            || oldIncidence->dtStart() != incidence->dtStart()
            || oldIncidence->dateTime(KCalCore::IncidenceBase::RoleEnd) != incidence->dateTime(KCalCore::IncidenceBase::RoleEnd)) {
            incidenceChanger()->deleteFinished(0, { item.id() }, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
            incidenceChanger()->createFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
        } else {
            incidenceChanger()->modifyFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
        }
    });
    connect(mMonitor, &Akonadi::Monitor::itemRemoved,
            this, [this](const Akonadi::Item &item) {
        incidenceChanger()->deleteFinished(0, { item.id() }, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
    });
    connect(mMonitor, &Akonadi::Monitor::collectionRemoved,
            this, &EventModel::removeCalendar);
}

void EventModel::addCalendar(const Akonadi::Collection &col)
{
    if (!mCols.contains(col)) {
        mCols.push_back(col);

        createMonitor();
        mMonitor->setCollectionMonitored(col, true);

        populateCollection(col);
    }
}

void EventModel::removeCalendar(const Akonadi::Collection &col)
{
    auto it = std::find(mCols.begin(), mCols.end(), col);
    if (it != mCols.end()) {
        mCols.erase(it);
        if (mMonitor) {
            mMonitor->setCollectionMonitored(col, false);
        }

        removeCollection(col);
    }
}

QVector<Akonadi::Collection> EventModel::collections() const
{
    return mCols;
}

Akonadi::Collection EventModel::collection(qint64 id) const
{
    auto it = std::find(mCols.cbegin(), mCols.cend(), Akonadi::Collection(id));
    return it == mCols.cend() ? Akonadi::Collection(id) : *it;
}

void EventModel::populateCollection(const Akonadi::Collection &col)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Populating events from collection" << col.id();
    auto job = new Akonadi::ItemFetchJob(col, this);
    job->fetchScope().fetchFullPayload(true);
    job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);
    job->setDeliveryOption(Akonadi::ItemFetchJob::EmitItemsInBatches);
    mFetchJobs.insert(col.id(), job);
    connect(job, &Akonadi::ItemFetchJob::itemsReceived,
            this, &EventModel::onItemsReceived);
    connect(job, &Akonadi::ItemFetchJob::result,
            job, [this, col](KJob *job) {
        mFetchJobs.remove(col.id());
        auto fetch = qobject_cast<Akonadi::ItemFetchJob *>(job);
        qCDebug(PIMEVENTSPLUGIN_LOG) << "Received" << fetch->count() << "events for collection" << col.id();
    });
}

void EventModel::onItemsReceived(const Akonadi::Item::List &items)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Batch: received" << items.count() << "items";
    for (const auto &item : items) {
        incidenceChanger()->createFinished(0, item,
                                           Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
    }
}

void EventModel::removeCollection(const Akonadi::Collection &col)
{
    if (KJob *job = mFetchJobs.take(col.id())) {
        disconnect(job, nullptr, this, nullptr);
        job->kill();
    }

    const auto items = this->items(col.id());
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Removing" << items.count() << "events for collection" << col.id();
    if (items.isEmpty()) {
        return;
    }

    QVector<Akonadi::Item::Id> ids;
    ids.reserve(items.size());
    std::transform(items.cbegin(), items.cend(), std::back_inserter(ids),
                   std::mem_fn(&Akonadi::Item::id));

    incidenceChanger()->deleteFinished(0, ids, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
}
