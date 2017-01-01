/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "createeventjob.h"
#include "createeventplugin_debug.h"
#include <Akonadi/KMime/MessageParts>
#include <AkonadiCore/ItemFetchJob>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/ItemCreateJob>
#include <AkonadiCore/RelationCreateJob>

#include <KMime/Message>

using namespace MessageViewer;

CreateEventJob::CreateEventJob(const KCalCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent)
    : KJob(parent),
      mItem(item),
      mCollection(collection),
      mEventPtr(eventPtr)
{
}

CreateEventJob::~CreateEventJob()
{
}

void CreateEventJob::start()
{
    // We need the full payload to attach the mail to the incidence
    if (!mItem.loadedPayloadParts().contains(Akonadi::MessagePart::Body)) {
        Akonadi::ItemFetchJob *job = new Akonadi::ItemFetchJob(mItem);
        job->fetchScope().fetchFullPayload();
        connect(job, &Akonadi::ItemFetchJob::result, this, &CreateEventJob::slotFetchDone);
    } else {
        createEvent();
    }
}

void CreateEventJob::slotFetchDone(KJob *job)
{
    Akonadi::ItemFetchJob *fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    if (fetchJob->items().count() == 1) {
        mItem = fetchJob->items().at(0);
    } else {
        Q_EMIT emitResult();
        return;
    }
    createEvent();
}

void CreateEventJob::createEvent()
{
    if (!mItem.hasPayload<KMime::Message::Ptr>()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << " item has not payload";
        Q_EMIT emitResult();
        return;
    }

    Akonadi::Item newEventItem;
    newEventItem.setMimeType(KCalCore::Event::eventMimeType());
    newEventItem.setPayload<KCalCore::Event::Ptr>(mEventPtr);

    Akonadi::ItemCreateJob *createJob = new Akonadi::ItemCreateJob(newEventItem, mCollection);
    connect(createJob, &Akonadi::ItemCreateJob::result, this, &CreateEventJob::slotEventCreated);
}

void CreateEventJob::slotEventCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << "Error during create new Event " << job->errorString();
        setError(job->error());
        setErrorText(job->errorText());
        Q_EMIT emitResult();
    } else {
        Akonadi::ItemCreateJob *createJob = static_cast<Akonadi::ItemCreateJob *>(job);
        Akonadi::Relation relation(Akonadi::Relation::GENERIC, mItem, createJob->item());
        Akonadi::RelationCreateJob *rJob = new Akonadi::RelationCreateJob(relation);
        connect(rJob, &Akonadi::RelationCreateJob::result, this, &CreateEventJob::slotRelationCreated);
    }
}

void CreateEventJob::slotRelationCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << "Error during create new Event " << job->errorString();
    }
    Q_EMIT emitResult();
}
