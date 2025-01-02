/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createeventjob.h"
#include "createeventplugin_debug.h"
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/MessageParts>

#include <KMime/Message>

using namespace MessageViewer;

CreateEventJob::CreateEventJob(const KCalendarCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent)
    : KJob(parent)
    , mItem(item)
    , mCollection(collection)
    , mEventPtr(eventPtr)
{
}

CreateEventJob::~CreateEventJob() = default;

void CreateEventJob::start()
{
    // We need the full payload to attach the mail to the incidence
    if (!mItem.loadedPayloadParts().contains(Akonadi::MessagePart::Body)) {
        auto job = new Akonadi::ItemFetchJob(mItem);
        job->fetchScope().fetchFullPayload();
        connect(job, &Akonadi::ItemFetchJob::result, this, &CreateEventJob::slotFetchDone);
    } else {
        createEvent();
    }
}

void CreateEventJob::slotFetchDone(KJob *job)
{
    auto fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    if (fetchJob->items().count() == 1) {
        mItem = fetchJob->items().at(0);
    } else {
        emitResult();
        return;
    }
    createEvent();
}

void CreateEventJob::createEvent()
{
    if (!mItem.hasPayload<KMime::Message::Ptr>()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << " item has not payload";
        emitResult();
        return;
    }

    Akonadi::Item newEventItem;
    newEventItem.setMimeType(KCalendarCore::Event::eventMimeType());
    newEventItem.setPayload<KCalendarCore::Event::Ptr>(mEventPtr);

    auto createJob = new Akonadi::ItemCreateJob(newEventItem, mCollection);
    connect(createJob, &Akonadi::ItemCreateJob::result, this, &CreateEventJob::slotEventCreated);
}

void CreateEventJob::slotEventCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << "Error during create new Event " << job->errorString();
        setError(job->error());
        setErrorText(job->errorText());
    }
    emitResult();
}

#include "moc_createeventjob.cpp"
