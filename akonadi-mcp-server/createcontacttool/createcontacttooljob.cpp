/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "createcontacttooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <KJob>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

CreateContactToolJob::CreateContactToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

CreateContactToolJob::~CreateContactToolJob() = default;

void CreateContactToolJob::setContact(const KContacts::Addressee &contact)
{
    mContact = contact;
}

void CreateContactToolJob::setAddressBookId(Akonadi::Collection::Id id)
{
    mAddressBookId = id;
}

bool CreateContactToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mContact.isEmpty();
}

QString CreateContactToolJob::invalidArgumentsMessage() const
{
    return i18n("Contact is empty");
}

void CreateContactToolJob::startJob()
{
    if (mAddressBookId >= 0) {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection(mAddressBookId), Akonadi::CollectionFetchJob::Base, this);
        connect(fetchJob, &KJob::result, this, &CreateContactToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    } else {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
        fetchJob->fetchScope().setContentMimeTypes({KContacts::Addressee::mimeType()});
        connect(fetchJob, &KJob::result, this, &CreateContactToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    }
}

void CreateContactToolJob::slotCollectionFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Address book fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual() || !collection.contentMimeTypes().contains(KContacts::Addressee::mimeType())
            || !(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            continue;
        }
        createContact(collection);
        return;
    }
    if (mAddressBookId >= 0) {
        finish(i18n("Address book %1 does not exist or does not accept new contacts", mAddressBookId), true);
    } else {
        finish(i18n("No writable address book found"), true);
    }
}

void CreateContactToolJob::createContact(const Akonadi::Collection &collection)
{
    Akonadi::Item item;
    item.setMimeType(KContacts::Addressee::mimeType());
    item.setPayload<KContacts::Addressee>(mContact);

    auto createJob = new Akonadi::ItemCreateJob(item, collection, this);
    createJob->setProperty("addressBookName", collection.displayName());
    connect(createJob, &KJob::result, this, &CreateContactToolJob::slotItemCreateResult);
    setCurrentJob(createJob);
}

void CreateContactToolJob::slotItemCreateResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact creation failed: %1"))) {
        return;
    }
    const Akonadi::Item item = qobject_cast<Akonadi::ItemCreateJob *>(job)->item();
    finish(i18n("Contact \"%1\" created in address book \"%2\" (item id: %3)",
                mContact.formattedName(),
                job->property("addressBookName").toString(),
                QString::number(item.id())));
}

#include "moc_createcontacttooljob.cpp"
