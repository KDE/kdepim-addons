/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>
  based on code from SPDX-FileCopyrightText: 2014 Clément Vannier <clement.vannier@free.fr>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailsenderjob.h"

#include "kaddressbook_sendmailplugin_debug.h"
#include <KEmailAddress>
#include <KJob>
#include <KLocalizedString>

#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>

#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

using namespace KABMailSender;

MailSenderJob::MailSenderJob(const Akonadi::Item::List &listItem, QObject *parent)
    : QObject(parent)
    , mListItem(listItem)
{
}

MailSenderJob::~MailSenderJob() = default;

void MailSenderJob::start()
{
    for (const Akonadi::Item &item : std::as_const(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const auto contact = item.payload<KContacts::Addressee>();
            const QString preferredEmail = contact.preferredEmail();
            if (!preferredEmail.isEmpty() && !mEmailAddresses.contains(preferredEmail)) {
                if (KEmailAddress::isValidSimpleAddress(contact.preferredEmail())) {
                    mEmailAddresses << KEmailAddress::normalizedAddress(contact.formattedName(), preferredEmail);
                }
            }
        } else if (item.hasPayload<KContacts::ContactGroup>()) {
            const auto group = item.payload<KContacts::ContactGroup>();
            unsigned int nbDataCount(group.dataCount());
            for (unsigned int i = 0; i < nbDataCount; ++i) {
                const QString currentEmail(group.data(i).email());
                if (KEmailAddress::isValidSimpleAddress(currentEmail)) {
                    const QString email = KEmailAddress::normalizedAddress(group.data(i).name(), currentEmail);
                    if (!email.isEmpty() && !mEmailAddresses.contains(email)) {
                        mEmailAddresses << email;
                    }
                }
            }
            const unsigned int nbContactReference(group.contactReferenceCount());
            for (unsigned int i = 0; i < nbContactReference; ++i) {
                KContacts::ContactGroup::ContactReference reference = group.contactReference(i);

                Akonadi::Item newItem;
                if (reference.gid().isEmpty()) {
                    newItem.setId(reference.uid().toLongLong());
                } else {
                    newItem.setGid(reference.gid());
                }
                mItemToFetch << newItem;
            }
        }
    }

    if (mItemToFetch.isEmpty()) {
        finishJob();
    } else {
        fetchNextItem();
    }
}

void MailSenderJob::fetchNextItem()
{
    if (mFetchJobCount < mItemToFetch.count()) {
        fetchItem(mItemToFetch.at(mFetchJobCount));
        ++mFetchJobCount;
    } else {
        finishJob();
    }
}

void MailSenderJob::fetchItem(const Akonadi::Item &item)
{
    auto job = new Akonadi::ItemFetchJob(item, this);
    job->fetchScope().fetchFullPayload();

    connect(job, &Akonadi::ItemFetchJob::result, this, &MailSenderJob::slotFetchJobFinished);
}

void MailSenderJob::slotFetchJobFinished(KJob *job)
{
    if (job->error()) {
        qCDebug(KADDRESSBOOK_SENDMAIL_LOG) << " error during fetching " << job->errorString();
        fetchNextItem();
        return;
    }

    auto fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);

    if (fetchJob->items().count() != 1) {
        fetchNextItem();
        return;
    }

    const Akonadi::Item item = fetchJob->items().at(0);
    const auto contact = item.payload<KContacts::Addressee>();

    if (!contact.preferredEmail().isEmpty()) {
        if (KEmailAddress::isValidSimpleAddress(contact.preferredEmail())) {
            mEmailAddresses << KEmailAddress::normalizedAddress(contact.formattedName(), contact.preferredEmail());
        }
    }
    fetchNextItem();
}

void MailSenderJob::finishJob()
{
    if (!mEmailAddresses.isEmpty()) {
        Q_EMIT sendMails(mEmailAddresses);
    } else {
        Q_EMIT sendMailsError(i18n("No emails found in selected contacts."));
    }
    deleteLater();
}

#include "moc_mailsenderjob.cpp"
