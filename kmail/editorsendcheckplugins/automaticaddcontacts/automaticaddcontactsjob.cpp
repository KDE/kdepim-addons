/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "automaticaddcontactsjob.h"
#include "automaticaddcontactsplugin_debug.h"
#include <Libkdepim/AddEmailAddressJob>
#include <AkonadiCore/CollectionFetchJob>
#include <AkonadiCore/CollectionFetchScope>
#include <AkonadiCore/AgentInstanceCreateJob>
#include <KContacts/Addressee>
#include <KMessageBox>
#include <KLocalizedString>
#include <AkonadiWidgets/AgentTypeDialog>

AutomaticAddContactsJob::AutomaticAddContactsJob(QObject *parent)
    : QObject(parent),
      mCurrentIndex(0)
{

}

AutomaticAddContactsJob::~AutomaticAddContactsJob()
{

}

void AutomaticAddContactsJob::start()
{
    if (mEmails.isEmpty()) {
        deleteLater();
        return;
    } else {
        if (!mCollection.isValid()) {
            qCDebug(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Invalid collection";
            deleteLater();
            return;
        }
    }
    mCurrentIndex = 0;
    //1) fetch collection to be sure that it's ok
    fetchCollection();
    addNextContact();
    //TODO
    //Remove it when implemented
    deleteLater();

}

void AutomaticAddContactsJob::fetchCollection()
{
    Akonadi::CollectionFetchJob *const addressBookJob = new Akonadi::CollectionFetchJob(mCollection, Akonadi::CollectionFetchJob::Base);

    const QStringList mimeTypes(KContacts::Addressee::mimeType());
    addressBookJob->fetchScope().setContentMimeTypes(mimeTypes);
    connect(addressBookJob, &KJob::result, this, &AutomaticAddContactsJob::slotCollectionsFetched);
}

void AutomaticAddContactsJob::slotCollectionsFetched(KJob *job)
{
#if 0
    if (job->error()) {
        if (KMessageBox::questionYesNo(
                    0,
                    i18nc("@info",
                          "You must create an address book before adding a contact. Do you want to create an address book?"),
                    i18nc("@title:window", "No Address Book Available")) == KMessageBox::Yes) {
            Akonadi::AgentTypeDialog dlg(mParentWidget);
            dlg.setWindowTitle(i18n("Add Address Book"));
            dlg.agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
            dlg.agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

            if (dlg.exec()) {
                const Akonadi::AgentType agentType = dlg.agentType();

                if (agentType.isValid()) {
                    Akonadi::AgentInstanceCreateJob *job = new Akonadi::AgentInstanceCreateJob(agentType, q);
                    connect(job, SIGNAL(result(KJob*)), SLOT(slotResourceCreationDone(KJob*)));
                    job->configure(mParentWidget);
                    job->start();
                    return;
                } else {
                    deleteLater();
                    return;
                }
            } else { //Canceled create agent => return error and finish job
                deleteLater();
                return;
            }
        } else {
            deleteLater();
            return;
        }
    } else if (nbItemCollection == 1) {
        addressBook = canCreateItemCollections[0];
    } else {
        // ask user in which address book the new contact shall be stored
        QPointer<Akonadi::SelectAddressBookDialog> dlg = new Akonadi::SelectAddressBookDialog(mParentWidget);

        bool gotIt = true;
        if (dlg->exec()) {
            addressBook = dlg->selectedCollection();
        } else {
            q->setError(UserDefinedError);
            q->emitResult();
            gotIt = false;
        }
        delete dlg;
        if (!gotIt) {
            return;
        }
    }

    if (!addressBook.isValid()) {
        q->setError(UserDefinedError);
        q->emitResult();
        return;
    }
#endif
}

void AutomaticAddContactsJob::verifyContactExist()
{
#if 0
    Akonadi::ContactSearchJob *searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, d->mEmail.toLower(),
                        Akonadi::ContactSearchJob::ExactMatch);
    connect(searchJob, SIGNAL(result(KJob*)), SLOT(slotSearchDone(KJob*)));
#endif

}

void AutomaticAddContactsJob::addNextContact()
{
    if (mCurrentIndex < mEmails.count()) {

    } else {
        deleteLater();
    }
}

void AutomaticAddContactsJob::setEmails(const QStringList &emails)
{
    mEmails = emails;
}

void AutomaticAddContactsJob::setCollection(const Akonadi::Collection &collection)
{
    mCollection = collection;
}
