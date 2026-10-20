/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "createcontactgrouptooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KContacts/Addressee>
#include <KLocalizedString>

CreateContactGroupToolJob::CreateContactGroupToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

CreateContactGroupToolJob::~CreateContactGroupToolJob() = default;

void CreateContactGroupToolJob::setName(const QString &name)
{
    mName = name;
}

void CreateContactGroupToolJob::setContactIds(const QList<Akonadi::Item::Id> &contactIds)
{
    mContactIds = contactIds;
}

void CreateContactGroupToolJob::setEmails(const QStringList &emails)
{
    mEmails = emails;
}

void CreateContactGroupToolJob::setAddressBookId(Akonadi::Collection::Id id)
{
    mAddressBookId = id;
}

bool CreateContactGroupToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mName.isEmpty();
}

QString CreateContactGroupToolJob::invalidArgumentsMessage() const
{
    return i18n("Contact group name is empty");
}

void CreateContactGroupToolJob::startJob()
{
    mContactGroup = KContacts::ContactGroup(mName);
    for (const QString &rawEmail : std::as_const(mEmails)) {
        QString fullName;
        QString email;
        KContacts::Addressee::parseEmailAddress(rawEmail, fullName, email);
        if (email.isEmpty()) {
            finish(i18n("Invalid email address \"%1\"", rawEmail), true);
            return;
        }
        mContactGroup.append(KContacts::ContactGroup::Data(fullName, email));
    }

    if (mContactIds.isEmpty()) {
        fetchAddressBook();
        return;
    }
    // Fetch the members first to make sure that they are contacts
    Akonadi::Item::List items;
    items.reserve(mContactIds.count());
    for (const Akonadi::Item::Id id : std::as_const(mContactIds)) {
        items.append(Akonadi::Item(id));
    }
    auto fetchJob = new Akonadi::ItemFetchJob(items, this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &CreateContactGroupToolJob::slotContactFetchResult);
    setCurrentJob(fetchJob);
}

void CreateContactGroupToolJob::slotContactFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    for (const Akonadi::Item::Id id : std::as_const(mContactIds)) {
        const auto it = std::find_if(items.cbegin(), items.cend(), [id](const Akonadi::Item &item) {
            return item.id() == id;
        });
        if (it == items.cend()) {
            finish(i18n("Contact %1 not found", id), true);
            return;
        }
        if (!it->hasPayload<KContacts::Addressee>()) {
            finish(i18n("Item %1 is not a contact", id), true);
            return;
        }
        // Akonadi stores the item id as uid of the reference (see Akonadi::ContactGroupExpandJob)
        mContactGroup.append(KContacts::ContactGroup::ContactReference(QString::number(id)));
    }
    fetchAddressBook();
}

void CreateContactGroupToolJob::fetchAddressBook()
{
    if (mAddressBookId >= 0) {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection(mAddressBookId), Akonadi::CollectionFetchJob::Base, this);
        connect(fetchJob, &KJob::result, this, &CreateContactGroupToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    } else {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
        fetchJob->fetchScope().setContentMimeTypes({KContacts::ContactGroup::mimeType()});
        connect(fetchJob, &KJob::result, this, &CreateContactGroupToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    }
}

void CreateContactGroupToolJob::slotCollectionFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Address book fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual() || !collection.contentMimeTypes().contains(KContacts::ContactGroup::mimeType())
            || !(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            continue;
        }
        createContactGroup(collection);
        return;
    }
    if (mAddressBookId >= 0) {
        finish(i18n("Address book %1 does not exist or does not accept new contact groups", mAddressBookId), true);
    } else {
        finish(i18n("No writable address book found"), true);
    }
}

void CreateContactGroupToolJob::createContactGroup(const Akonadi::Collection &collection)
{
    Akonadi::Item item;
    item.setMimeType(KContacts::ContactGroup::mimeType());
    item.setPayload<KContacts::ContactGroup>(mContactGroup);

    auto createJob = new Akonadi::ItemCreateJob(item, collection, this);
    createJob->setProperty("addressBookName", collection.displayName());
    connect(createJob, &KJob::result, this, &CreateContactGroupToolJob::slotItemCreateResult);
    setCurrentJob(createJob);
}

void CreateContactGroupToolJob::slotItemCreateResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact group creation failed: %1"))) {
        return;
    }
    const Akonadi::Item item = qobject_cast<Akonadi::ItemCreateJob *>(job)->item();
    finish(i18np("Contact group \"%2\" with %1 member created in address book \"%3\" (item id: %4)",
                 "Contact group \"%2\" with %1 members created in address book \"%3\" (item id: %4)",
                 mContactGroup.count(),
                 mName,
                 job->property("addressBookName").toString(),
                 QString::number(item.id())));
}

#include "moc_createcontactgrouptooljob.cpp"
