/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createtodojob.h"
#include "createtodoplugin_debug.h"
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/MessageParts>
#include <Akonadi/RelationCreateJob>

#include <KMime/Message>

using namespace MessageViewer;

CreateTodoJob::CreateTodoJob(const KCalendarCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent)
    : KJob(parent)
    , mItem(item)
    , mCollection(collection)
    , mTodoPtr(todoPtr)
{
}

CreateTodoJob::~CreateTodoJob()
{
    qCDebug(CREATETODOPLUGIN_LOG) << " CreateTodoJob::~CreateTodoJob()";
}

void CreateTodoJob::start()
{
    // We need the full payload to attach the mail to the incidence
    if (!mItem.loadedPayloadParts().contains(Akonadi::MessagePart::Body)) {
        auto job = new Akonadi::ItemFetchJob(mItem);
        job->fetchScope().fetchFullPayload();
        connect(job, &Akonadi::ItemFetchJob::result, this, &CreateTodoJob::slotFetchDone);
    } else {
        createTodo();
    }
}

void CreateTodoJob::slotFetchDone(KJob *job)
{
    auto fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    if (fetchJob->items().count() == 1) {
        mItem = fetchJob->items().at(0);
    } else {
        qCDebug(CREATETODOPLUGIN_LOG) << " createTodo Error during fetch: " << job->errorString();
        emitResult();
        return;
    }
    createTodo();
}

void CreateTodoJob::createTodo()
{
    if (!mItem.hasPayload<KMime::Message::Ptr>()) {
        qCDebug(CREATETODOPLUGIN_LOG) << " item has not payload";
        emitResult();
        return;
    }

    Akonadi::Item newTodoItem;
    newTodoItem.setMimeType(KCalendarCore::Todo::todoMimeType());
    newTodoItem.setPayload<KCalendarCore::Todo::Ptr>(mTodoPtr);

    auto createJob = new Akonadi::ItemCreateJob(newTodoItem, mCollection);
    connect(createJob, &Akonadi::ItemCreateJob::result, this, &CreateTodoJob::todoCreated);
}

void CreateTodoJob::todoCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATETODOPLUGIN_LOG) << "Error during create new Todo " << job->errorString();
        setError(job->error());
        setErrorText(job->errorText());
        emitResult();
    } else {
        auto createJob = static_cast<Akonadi::ItemCreateJob *>(job);
        Akonadi::Relation relation(Akonadi::Relation::GENERIC, mItem, createJob->item());
        auto rJob = new Akonadi::RelationCreateJob(relation);
        connect(rJob, &Akonadi::RelationCreateJob::result, this, &CreateTodoJob::relationCreated);
    }
}

void CreateTodoJob::relationCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATETODOPLUGIN_LOG) << "Error during create new Todo " << job->errorString();
    }
    emitResult();
}

#include "moc_createtodojob.cpp"
