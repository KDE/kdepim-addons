/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "eventmodel.h"
#include "pimeventsplugin_debug.h"

#include <Akonadi/IncidenceChanger>

#include <Akonadi/AttributeFactory>
#include <Akonadi/CollectionColorAttribute>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/Monitor>

EventModel::EventModel(QObject *parent)
    : Akonadi::CalendarBase(parent)
{
    Akonadi::AttributeFactory::registerAttribute<Akonadi::CollectionColorAttribute>();
}

EventModel::~EventModel() = default;

void EventModel::createMonitor()
{
    if (mMonitor) {
        return;
    }

    mMonitor = new Akonadi::Monitor(this);
    mMonitor->setObjectName(QStringLiteral("PlasmaEventModelMonitor"));
    mMonitor->itemFetchScope().fetchFullPayload(true);
    mMonitor->collectionFetchScope().fetchAttribute<Akonadi::EntityDisplayAttribute>();
    mMonitor->collectionFetchScope().fetchAttribute<Akonadi::CollectionColorAttribute>();
    mMonitor->fetchCollection(true);

    connect(mMonitor, &Akonadi::Monitor::itemAdded, this, [this](const Akonadi::Item &item) {
        // This is super-ugly, but the only way how to insert into CalendarBase
        // without having direct access to CalendarBasePrivate.
        // changeId is luckily ignored by CalendarBase.
        Q_EMIT incidenceChanger()->createFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
    });
    connect(mMonitor, &Akonadi::Monitor::itemChanged, this, [this](const Akonadi::Item &item) {
        if (!item.hasPayload<KCalendarCore::Incidence::Ptr>()) {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "Item" << item.id() << "has no payload!";
            return;
        }

        auto incidence = item.payload<KCalendarCore::Incidence::Ptr>();
        if (!incidence) {
            return; // HUH?!
        }
        const KCalendarCore::Incidence::Ptr oldIncidence = this->incidence(incidence->instanceIdentifier());
        if (!oldIncidence) {
            // Change for event we don't know about -> discard
            return;
        }

        // Unfortunately the plasma applet does not handle event moves
        // so we have to simulate via remove+add
        if (oldIncidence->allDay() != incidence->allDay() || oldIncidence->dtStart() != incidence->dtStart()
            || oldIncidence->dateTime(KCalendarCore::IncidenceBase::RoleEnd) != incidence->dateTime(KCalendarCore::IncidenceBase::RoleEnd)) {
            Q_EMIT incidenceChanger()->deleteFinished(0, {item.id()}, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
            Q_EMIT incidenceChanger()->createFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
        } else {
            Q_EMIT incidenceChanger()->modifyFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
        }
    });
    connect(mMonitor, &Akonadi::Monitor::itemRemoved, this, [this](const Akonadi::Item &item) {
        Q_EMIT incidenceChanger()->deleteFinished(0, {item.id()}, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
    });
    connect(mMonitor, &Akonadi::Monitor::collectionRemoved, this, &EventModel::removeCalendar);
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

QList<Akonadi::Collection> EventModel::collections() const
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
    connect(job, &Akonadi::ItemFetchJob::itemsReceived, this, &EventModel::onItemsReceived);
    connect(job, &Akonadi::ItemFetchJob::result, job, [this, col](KJob *job) {
        mFetchJobs.remove(col.id());
        auto fetch = qobject_cast<Akonadi::ItemFetchJob *>(job);
        qCDebug(PIMEVENTSPLUGIN_LOG) << "Received" << fetch->count() << "events for collection" << col.id();
    });
}

void EventModel::onItemsReceived(const Akonadi::Item::List &items)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << "Batch: received" << items.count() << "items";
    for (const auto &item : items) {
        if (item.hasPayload<KCalendarCore::Incidence::Ptr>()) {
            Q_EMIT incidenceChanger()->createFinished(0, item, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
        } else {
            qCDebug(PIMEVENTSPLUGIN_LOG) << "Item" << item.id() << "has no payload";
        }
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

    QList<Akonadi::Item::Id> ids;
    ids.reserve(items.size());
    std::transform(items.cbegin(), items.cend(), std::back_inserter(ids), std::mem_fn(&Akonadi::Item::id));

    Q_EMIT incidenceChanger()->deleteFinished(0, ids, Akonadi::IncidenceChanger::ResultCodeSuccess, QString());
}

#include "moc_eventmodel.cpp"
