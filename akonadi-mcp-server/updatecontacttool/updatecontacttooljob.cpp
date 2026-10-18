/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updatecontacttooljob.h"
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <KContacts/Addressee>
#include <KLocalizedString>

bool UpdateContactToolJob::ContactChanges::isEmpty() const
{
    return !name && !emails && !phoneNumbers && !organization && !birthday && !note;
}

UpdateContactToolJob::UpdateContactToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

UpdateContactToolJob::~UpdateContactToolJob() = default;

bool UpdateContactToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0 && !mChanges.isEmpty();
}

void UpdateContactToolJob::setItemId(qint64 itemId)
{
    mItemId = itemId;
}

void UpdateContactToolJob::setChanges(const ContactChanges &changes)
{
    mChanges = changes;
}

QString UpdateContactToolJob::invalidArgumentsMessage() const
{
    if (mItemId < 0) {
        return i18n("Contact id must be a positive integer");
    }
    return i18n("No field to update");
}

void UpdateContactToolJob::startJob()
{
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &UpdateContactToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void UpdateContactToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Contact %1 not found", mItemId), true);
        return;
    }
    Akonadi::Item item = items.at(0);
    if (!item.hasPayload<KContacts::Addressee>()) {
        finish(i18n("Item %1 is not a contact", mItemId), true);
        return;
    }
    auto contact = item.payload<KContacts::Addressee>();
    applyChanges(contact);
    item.setPayload<KContacts::Addressee>(contact);

    auto modifyJob = new Akonadi::ItemModifyJob(item, this);
    modifyJob->setProperty("contactName", contact.formattedName());
    connect(modifyJob, &KJob::result, this, &UpdateContactToolJob::slotItemModifyResult);
    setCurrentJob(modifyJob);
}

void UpdateContactToolJob::slotItemModifyResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact modification failed: %1"))) {
        return;
    }
    finish(i18n("Contact \"%1\" updated (item id: %2)", job->property("contactName").toString(), QString::number(mItemId)));
}

void UpdateContactToolJob::applyChanges(KContacts::Addressee &contact) const
{
    if (mChanges.name) {
        contact.setNameFromString(*mChanges.name);
        contact.setFormattedName(*mChanges.name);
    }
    if (mChanges.emails) {
        contact.setEmails(*mChanges.emails);
    }
    if (mChanges.phoneNumbers) {
        KContacts::PhoneNumber::List phoneNumbers;
        phoneNumbers.reserve(mChanges.phoneNumbers->count());
        for (const QString &phoneNumber : std::as_const(*mChanges.phoneNumbers)) {
            phoneNumbers.append(KContacts::PhoneNumber(phoneNumber));
        }
        contact.setPhoneNumbers(phoneNumbers);
    }
    if (mChanges.organization) {
        contact.setOrganization(*mChanges.organization);
    }
    if (mChanges.birthday) {
        contact.setBirthday(*mChanges.birthday);
    }
    if (mChanges.note) {
        contact.setNote(*mChanges.note);
    }
}

#include "moc_updatecontacttooljob.cpp"
