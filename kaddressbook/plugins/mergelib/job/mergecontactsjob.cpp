/*
    SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactsjob.h"
#include "mergecontacts.h"
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemDeleteJob>
#include <KContacts/Address>

#include "kaddressbookmergelibprivate_debug.h"

using namespace KABMergeContacts;

MergeContactsJob::MergeContactsJob(QObject *parent)
    : QObject(parent)
{
}

MergeContactsJob::~MergeContactsJob() = default;

bool MergeContactsJob::canStart() const
{
    if (!mCollection.isValid()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " mCollection is not valid !";
        return false;
    }
    if (mNewContact.isEmpty()) {
        if (mListItem.isEmpty()) {
            qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " list item is empty !";
            return false;
        }
    }
    return true;
}

void MergeContactsJob::start()
{
    if (!canStart()) {
        Q_EMIT finished(mCreatedContact);
        deleteLater();
        return;
    }
    generateMergedContact();
}

void MergeContactsJob::generateMergedContact()
{
    if (mNewContact.isEmpty()) {
        MergeContacts mergeContact(mListItem);
        const KContacts::Addressee newContact = mergeContact.mergedContact();
        if (newContact.isEmpty()) {
            Q_EMIT finished(mCreatedContact);
            deleteLater();
            return;
        }
        createMergedContact(newContact);
    } else {
        createMergedContact(mNewContact);
    }
}

void MergeContactsJob::setNewContact(const KContacts::Addressee &addr)
{
    mNewContact = addr;
}

void MergeContactsJob::setListItem(const Akonadi::Item::List &lstItem)
{
    mListItem = lstItem;
}

void MergeContactsJob::setDestination(const Akonadi::Collection &collection)
{
    mCollection = collection;
}

void MergeContactsJob::createMergedContact(const KContacts::Addressee &addressee)
{
    Akonadi::Item item;
    item.setMimeType(KContacts::Addressee::mimeType());
    item.setPayload<KContacts::Addressee>(addressee);

    auto job = new Akonadi::ItemCreateJob(item, mCollection, this);
    connect(job, &Akonadi::ItemCreateJob::result, this, &MergeContactsJob::slotCreateMergedContactFinished);
}

void MergeContactsJob::slotCreateMergedContactFinished(KJob *job)
{
    if (job->error()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << job->errorString();
        Q_EMIT finished(mCreatedContact);
        deleteLater();
        return;
    }
    auto createdJob = qobject_cast<Akonadi::ItemCreateJob *>(job);
    mCreatedContact = createdJob->item();

    if (!mListItem.isEmpty()) {
        auto deleteJob = new Akonadi::ItemDeleteJob(mListItem, this);
        connect(deleteJob, &Akonadi::ItemDeleteJob::result, this, &MergeContactsJob::slotDeleteContactsFinished);
    } else {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " mListITem is empty. We can't delete it";
    }
}

void MergeContactsJob::slotDeleteContactsFinished(KJob *job)
{
    if (job->error()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << job->errorString();
    }
    Q_EMIT finished(mCreatedContact);
    deleteLater();
}

#include "moc_mergecontactsjob.cpp"
