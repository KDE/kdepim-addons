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
    //TODO
    //Remove it when implemented
    deleteLater();

}

void AutomaticAddContactsJob::fetchCollection()
{
    Akonadi::CollectionFetchJob *const addressBookJob = new Akonadi::CollectionFetchJob(mCollection, Akonadi::CollectionFetchJob::Base);

    const QStringList mimeTypes(KContacts::Addressee::mimeType());
    addressBookJob->fetchScope().setContentMimeTypes(mimeTypes);
    connect(addressBookJob, &KJob::result, this, &AutomaticAddContactsJob::slotSelectedCollectionFetched);
}

void AutomaticAddContactsJob::slotSelectedCollectionFetched(KJob *job)
{
    if (job->error()) {
        //Collection not found.
        //fetch all collection
        const QStringList mimeTypes(KContacts::Addressee::mimeType());

        Akonadi::CollectionFetchJob *const addressBookJob =
            new Akonadi::CollectionFetchJob(Akonadi::Collection::root(),
                                            Akonadi::CollectionFetchJob::Recursive);

        addressBookJob->fetchScope().setContentMimeTypes(mimeTypes);
        connect(addressBookJob, &KJob::result, this, &AutomaticAddContactsJob::slotFetchAllCollections);
        return;
    }
    const Akonadi::CollectionFetchJob *addressBookJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
    mCollection = addressBookJob->collections().at(0);
    addNextContact();
}


void AutomaticAddContactsJob::slotFetchAllCollections(KJob*)
{
#if 0
    if (job->error()) {
        q->setError(job->error());
        q->setErrorText(job->errorText());
        q->emitResult();
        return;
    }

    const Akonadi::CollectionFetchJob *addressBookJob =
        qobject_cast<Akonadi::CollectionFetchJob *>(job);

    Akonadi::Collection::List canCreateItemCollections;

    foreach (const Akonadi::Collection &collection, addressBookJob->collections()) {
        if (Akonadi::Collection::CanCreateItem & collection.rights()) {
            canCreateItemCollections.append(collection);
        }
    }

    Akonadi::Collection addressBook;

    const int nbItemCollection(canCreateItemCollections.size());
    if (nbItemCollection == 0) {
        if (KMessageBox::questionYesNo(
                    mParentWidget,
                    i18nc("@info",
                          "You must create an address book before adding a contact. Do you want to create an address book?"),
                    i18nc("@title:window", "No Address Book Available")) == KMessageBox::Yes) {
            Akonadi::AgentTypeDialog dlg(mParentWidget);
            dlg.setWindowTitle(i18n("Add Address Book"));
            dlg.agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
            dlg.agentFilterProxyModel()->addMimeTypeFilter(KContacts::ContactGroup::mimeType());
            dlg.agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

            if (dlg.exec()) {
                const Akonadi::AgentType agentType = dlg.agentType();

                if (agentType.isValid()) {
                    Akonadi::AgentInstanceCreateJob *job = new Akonadi::AgentInstanceCreateJob(agentType, q);
                    q->connect(job, SIGNAL(result(KJob*)), SLOT(slotResourceCreationDone(KJob*)));
                    job->configure(mParentWidget);
                    job->start();
                    return;
                } else { //if agent is not valid => return error and finish job
                    q->setError(UserDefinedError);
                    q->emitResult();
                    return;
                }
            } else { //Canceled create agent => return error and finish job
                q->setError(UserDefinedError);
                q->emitResult();
                return;
            }
        } else {
            q->setError(UserDefinedError);
            q->emitResult();
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
    KContacts::Addressee contact;
    contact.setNameFromString(mName);
    contact.insertEmail(mEmail, true);

    // create the new item
    Akonadi::Item item;
    item.setMimeType(KContacts::Addressee::mimeType());
    item.setPayload<KContacts::Addressee>(contact);

    // save the new item in akonadi storage
    Akonadi::ItemCreateJob *createJob = new Akonadi::ItemCreateJob(item, addressBook, q);
    q->connect(createJob, SIGNAL(result(KJob*)), SLOT(slotAddContactDone(KJob*)));
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

void AutomaticAddContactsJob::slotSearchDone(KJob *job)
{
    //TODO
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
