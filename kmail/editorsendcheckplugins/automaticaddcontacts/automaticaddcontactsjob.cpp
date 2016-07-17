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
#include <KContacts/ContactGroup>
#include <KMessageBox>
#include <KLocalizedString>
#include <AkonadiWidgets/AgentTypeDialog>
#include <Akonadi/Contact/ContactSearchJob>
#include <AkonadiCore/ItemCreateJob>
#include <KEmailAddress>
#include <QPointer>
#include <akonadi/contact/selectaddressbookdialog.h>
#include <AkonadiCore/AgentFilterProxyModel>

//#define IMPLEMENTATION_DONE 1


AutomaticAddContactsJob::AutomaticAddContactsJob(QObject *parent)
    : QObject(parent),
      mCurrentIndex(-1)
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
    mCurrentIndex = -1;
#ifdef IMPLEMENTATION_DONE
    fetchCollection();
#else
    deleteLater();
#endif
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


void AutomaticAddContactsJob::slotFetchAllCollections(KJob *job)
{
    if (job->error()) {
        deleteLater();
        return;
    }

    const Akonadi::CollectionFetchJob *addressBookJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);

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
                    0,
                    i18nc("@info",
                          "You must create an address book before adding a contact. Do you want to create an address book?"),
                    i18nc("@title:window", "No Address Book Available")) == KMessageBox::Yes) {
            Akonadi::AgentTypeDialog dlg(0);
            dlg.setWindowTitle(i18n("Add Address Book"));
            dlg.agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
            dlg.agentFilterProxyModel()->addMimeTypeFilter(KContacts::ContactGroup::mimeType());
            dlg.agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

            if (dlg.exec()) {
                const Akonadi::AgentType agentType = dlg.agentType();

                if (agentType.isValid()) {
                    Akonadi::AgentInstanceCreateJob *job = new Akonadi::AgentInstanceCreateJob(agentType, this);
                    connect(job, &KJob::result, this, &AutomaticAddContactsJob::slotResourceCreationDone);
                    job->configure();
                    job->start();
                    return;
                } else { //if agent is not valid => return error and finish job
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
        QPointer<Akonadi::SelectAddressBookDialog> dlg = new Akonadi::SelectAddressBookDialog(0);

        bool gotIt = true;
        if (dlg->exec()) {
            addressBook = dlg->selectedCollection();
        } else {
            gotIt = false;
        }
        delete dlg;
        if (!gotIt) {
            qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to selected Addressbook selected not valid";
            deleteLater();
            return;
        }
    }

    if (!addressBook.isValid()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Addressbook selected not valid";
        deleteLater();
        return;
    }
    addNextContact();
}


void AutomaticAddContactsJob::slotResourceCreationDone(KJob *job)
{
    if (job->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to create resource:" << job->errorText();
        deleteLater();
        return;
    }
    addNextContact();
}

void AutomaticAddContactsJob::verifyContactExist()
{
    QString email = mEmails.at(mCurrentIndex);
    QString tname, temail;
    KEmailAddress::extractEmailAddressAndName(email, temail, tname);
    if (temail.isEmpty()) {
        addNextContact();
    } else {
        if (mProcessedEmails.contains(email)) {
            addNextContact();
        } else {
            mProcessEmail = email;
            mName = tname;
            mProcessedEmails.append(email);
            Akonadi::ContactSearchJob *searchJob = new Akonadi::ContactSearchJob(this);
            searchJob->setLimit(1);
            searchJob->setQuery(Akonadi::ContactSearchJob::Email, mProcessEmail.toLower(),
                                Akonadi::ContactSearchJob::ExactMatch);
            connect(searchJob, &KJob::result, this, &AutomaticAddContactsJob::slotSearchDone);
        }
    }

}

void AutomaticAddContactsJob::slotSearchDone(KJob *job)
{
    Akonadi::ContactSearchJob *searchJob = static_cast<Akonadi::ContactSearchJob *>(job);
    if (searchJob->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to fetch contact:" << searchJob->errorText();
    } else if (searchJob->contacts().isEmpty()) {
        KContacts::Addressee contact;
        contact.setNameFromString(mName);
        contact.insertEmail(mProcessEmail, true);

        // create the new item
        Akonadi::Item item;
        item.setMimeType(KContacts::Addressee::mimeType());
        item.setPayload<KContacts::Addressee>(contact);

        // save the new item in akonadi storage
        Akonadi::ItemCreateJob *createJob = new Akonadi::ItemCreateJob(item, mCollection, this);
        connect(createJob, &KJob::result, this, &AutomaticAddContactsJob::slotAddContactDone);
        return;
    }
    addNextContact();
}

void AutomaticAddContactsJob::slotAddContactDone(KJob *job)
{
    if (job->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Errorwhen add contact to addressbook:" << job->errorText();
    }
    addNextContact();
}

void AutomaticAddContactsJob::addNextContact()
{
    mCurrentIndex++;
    if (mCurrentIndex < mEmails.count()) {
        verifyContactExist();
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
