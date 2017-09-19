/*
   Copyright (C) 2012-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "updatecontactjob.h"
#include <Akonadi/Contact/ContactSearchJob>
#include <AkonadiCore/itemmodifyjob.h>
#include <kcontacts/addressee.h>
#include <KLocalizedString>
#include <kmessagebox.h>

UpdateContactJob::UpdateContactJob(const QString &email, const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , mEmail(email)
    , mContact(contact)
    , mParentWidget(parentWidget)
{
}

UpdateContactJob::~UpdateContactJob()
{
}

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
    Akonadi::ItemModifyJob *modifyJob = new Akonadi::ItemModifyJob(item);
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

    const QString text = i18n("The vCard was updated to your address book; "
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
    Akonadi::ContactSearchJob *searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, mEmail.toLower(),
                        Akonadi::ContactSearchJob::ExactMatch);

    connect(searchJob, &Akonadi::ContactSearchJob::result, this, &UpdateContactJob::slotSearchDone);
}

#include "moc_updatecontactjob.cpp"
