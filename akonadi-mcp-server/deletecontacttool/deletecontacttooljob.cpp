/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deletecontacttooljob.h"
#include <Akonadi/ItemDeleteJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KContacts/Addressee>
#include <KLocalizedString>

DeleteContactToolJob::DeleteContactToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

DeleteContactToolJob::~DeleteContactToolJob() = default;

bool DeleteContactToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0;
}

void DeleteContactToolJob::setItemId(qint64 itemId)
{
    mItemId = itemId;
}

QString DeleteContactToolJob::invalidArgumentsMessage() const
{
    return i18n("Contact id must be a positive integer");
}

void DeleteContactToolJob::startJob()
{
    // Fetch the item first to make sure that we only delete a contact
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &DeleteContactToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void DeleteContactToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Contact %1 not found", mItemId), true);
        return;
    }
    const Akonadi::Item &item = items.at(0);
    if (!item.hasPayload<KContacts::Addressee>()) {
        finish(i18n("Item %1 is not a contact", mItemId), true);
        return;
    }

    auto deleteJob = new Akonadi::ItemDeleteJob(item, this);
    deleteJob->setProperty("contactName", item.payload<KContacts::Addressee>().formattedName());
    connect(deleteJob, &KJob::result, this, &DeleteContactToolJob::slotItemDeleteResult);
    setCurrentJob(deleteJob);
}

void DeleteContactToolJob::slotItemDeleteResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact deletion failed: %1"))) {
        return;
    }
    finish(i18n("Contact \"%1\" deleted (item id: %2)", job->property("contactName").toString(), QString::number(mItemId)));
}

#include "moc_deletecontacttooljob.cpp"
