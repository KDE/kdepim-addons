/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "listaddressbookstooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>
#include <KJob>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

ListAddressBooksToolJob::ListAddressBooksToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

ListAddressBooksToolJob::~ListAddressBooksToolJob() = default;

void ListAddressBooksToolJob::startJob()
{
    auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
    fetchJob->fetchScope().setContentMimeTypes({KContacts::Addressee::mimeType(), KContacts::ContactGroup::mimeType()});
    connect(fetchJob, &KJob::result, this, &ListAddressBooksToolJob::slotResult);
    setCurrentJob(fetchJob);
}

void ListAddressBooksToolJob::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Address book fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    QStringList entries;
    entries.reserve(collections.count());
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual()) {
            continue;
        }
        const QStringList mimeTypes = collection.contentMimeTypes();
        if (!mimeTypes.contains(KContacts::Addressee::mimeType()) && !mimeTypes.contains(KContacts::ContactGroup::mimeType())) {
            continue;
        }
        QString entry = u"%1 (id: %2)"_s.arg(collection.displayName(), QString::number(collection.id()));
        if (!(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            entry += u" [read-only]"_s;
        }
        entries.append(entry);
    }
    if (entries.isEmpty()) {
        finish(i18n("No address book found"));
    } else {
        finish(entries.join(u'\n'));
    }
}

#include "moc_listaddressbookstooljob.cpp"
