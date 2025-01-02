/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updatecontactjob.h"
#include <Akonadi/ContactSearchJob>
#include <Akonadi/ItemModifyJob>
#include <KLocalizedString>
#include <KMessageBox>

UpdateContactJob::UpdateContactJob(const QString &email, const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , mEmail(email)
    , mContact(contact)
    , mParentWidget(parentWidget)
{
}

UpdateContactJob::~UpdateContactJob() = default;

void UpdateContactJob::slotSearchDone(KJob *job)
{
    if (job->error()) {
        setError(job->error());
        setErrorText(job->errorText());
        emitResult();
        return;
    }

    const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);

    const KContacts::Addressee::List contacts = searchJob->contacts();

    if (contacts.isEmpty()) {
        const QString text = i18n("The vCard's primary email address is not in addressbook.");
        KMessageBox::information(mParentWidget, text);
        setError(UserDefinedError);
        emitResult();
        return;
    } else if (contacts.count() > 1) {
        const QString text = i18n("There are two or more contacts with same email stored in addressbook.");
        KMessageBox::information(mParentWidget, text);
        setError(UserDefinedError);
        emitResult();
        return;
    }
    Akonadi::Item item = searchJob->items().at(0);
    item.setPayload<KContacts::Addressee>(mContact);
    auto modifyJob = new Akonadi::ItemModifyJob(item);
    connect(modifyJob, &Akonadi::ItemModifyJob::result, this, &UpdateContactJob::slotUpdateContactDone);
}

void UpdateContactJob::slotUpdateContactDone(KJob *job)
{
    if (job->error()) {
        setError(job->error());
        setErrorText(job->errorText());
        emitResult();
        return;
    }

    const QString text = i18n(
        "The vCard was updated in your address book; "
        "you can add more information to this "
        "entry by opening the address book.");
    KMessageBox::information(mParentWidget, text, QString(), QStringLiteral("updatedtokabc"));

    emitResult();
}

void UpdateContactJob::start()
{
    if (mEmail.isEmpty()) {
        const QString text = i18n("Email not specified");
        KMessageBox::information(mParentWidget, text);
        setError(UserDefinedError);
        emitResult();
        return;
    }
    // first check whether a contact with the same email exists already
    auto searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, mEmail.toLower(), Akonadi::ContactSearchJob::ExactMatch);

    connect(searchJob, &Akonadi::ContactSearchJob::result, this, &UpdateContactJob::slotSearchDone);
}

#include "moc_updatecontactjob.cpp"
