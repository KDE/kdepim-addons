/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "createnotejob.h"
#include "createnoteplugin_debug.h"
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemModifyJob>
#include <Akonadi/MessageParts>
#include <Akonadi/Relation>
#include <Akonadi/RelationCreateJob>

#include <KMime/Message>
#include <QCoreApplication>

using namespace MessageViewer;

CreateNoteJob::CreateNoteJob(const KMime::Message::Ptr &notePtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent)
    : KJob(parent)
    , mItem(item)
    , mCollection(collection)
    , mNote(notePtr)
{
}

CreateNoteJob::~CreateNoteJob() = default;

void CreateNoteJob::start()
{
    mNote.setFrom(QCoreApplication::applicationName() + QLatin1Char(' ') + QCoreApplication::applicationVersion());
    mNote.setLastModifiedDate(QDateTime::currentDateTimeUtc());
    if (!mItem.relations().isEmpty()) {
        Akonadi::Relation relation;
        const auto relations = mItem.relations();
        for (const Akonadi::Relation &r : relations) {
            // assuming that GENERIC relations to emails are notes is a pretty horrific hack imo - aseigo
            if (r.type() == Akonadi::Relation::GENERIC && r.right().mimeType() == Akonadi::NoteUtils::noteMimeType()) {
                relation = r;
                break;
            }
        }

        if (relation.isValid()) {
            Akonadi::Item item = relation.right();
            item.setMimeType(Akonadi::NoteUtils::noteMimeType());
            item.setPayload(mNote.message());
            auto modifyJob = new Akonadi::ItemModifyJob(item);
            connect(modifyJob, &Akonadi::ItemModifyJob::result, this, &CreateNoteJob::noteUpdated);
            return;
        }
    }

    Akonadi::Item newNoteItem;
    newNoteItem.setMimeType(Akonadi::NoteUtils::noteMimeType());
    newNoteItem.setPayload(mNote.message());
    auto createJob = new Akonadi::ItemCreateJob(newNoteItem, mCollection);
    connect(createJob, &Akonadi::ItemCreateJob::result, this, &CreateNoteJob::noteCreated);
}

void CreateNoteJob::noteCreated(KJob *job)
{
    if (job->error()) {
        qCWarning(CREATENOTEPLUGIN_LOG) << "Error during create new Note " << job->errorString();
        setError(job->error());
        setErrorText(job->errorText());
        emitResult();
    } else {
        auto createJob = static_cast<Akonadi::ItemCreateJob *>(job);
        Akonadi::Relation relation(Akonadi::Relation::GENERIC, mItem, createJob->item());
        auto rJob = new Akonadi::RelationCreateJob(relation);
        connect(rJob, &Akonadi::RelationCreateJob::result, this, &CreateNoteJob::relationCreated);
    }
}

void CreateNoteJob::noteUpdated(KJob *job)
{
    if (job->error()) {
        setError(job->error());
        setErrorText(job->errorText());
    }

    emitResult();
}

void CreateNoteJob::relationCreated(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATENOTEPLUGIN_LOG) << "Error during create new Note " << job->errorString();
    }
    emitResult();
}

#include "moc_createnotejob.cpp"
