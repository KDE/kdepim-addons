/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsjob.h"
#include "automaticaddcontactsplugin_debug.h"
#include <Akonadi/AgentFilterProxyModel>
#include <Akonadi/AgentInstanceCreateJob>
#include <Akonadi/AgentTypeDialog>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ContactSearchJob>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/SelectAddressBookDialog>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>
#include <KEmailAddress>
#include <KLocalizedString>
#include <KMessageBox>
#include <PimCommon/PimUtil>
#include <QPointer>

AutomaticAddContactsJob::AutomaticAddContactsJob(QObject *parent)
    : QObject(parent)
{
}

AutomaticAddContactsJob::~AutomaticAddContactsJob() = default;

void AutomaticAddContactsJob::start()
{
    if (mEmails.isEmpty()) {
        deleteLaterAndEmitSignal();
        return;
    } else {
        if (!mCollection.isValid()) {
            qCDebug(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Invalid collection";
            deleteLaterAndEmitSignal();
            return;
        }
    }
    mCurrentIndex = -1;
    fetchCollection();
}

void AutomaticAddContactsJob::fetchCollection()
{
    auto const addressBookJob = new Akonadi::CollectionFetchJob(mCollection, Akonadi::CollectionFetchJob::Base);

    const QStringList mimeTypes(KContacts::Addressee::mimeType());
    addressBookJob->fetchScope().setContentMimeTypes(mimeTypes);
    connect(addressBookJob, &KJob::result, this, &AutomaticAddContactsJob::slotSelectedCollectionFetched);
}

void AutomaticAddContactsJob::slotSelectedCollectionFetched(KJob *job)
{
    if (job->error()) {
        // Collection not found.
        // fetch all collection
        const QStringList mimeTypes(KContacts::Addressee::mimeType());

        auto const addressBookJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive);

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
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Error during AutomaticAddContactsJob::slotFetchAllCollections : " << job->errorString();
        deleteLaterAndEmitSignal();
        return;
    }

    const Akonadi::CollectionFetchJob *addressBookJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);

    Akonadi::Collection::List canCreateItemCollections;
    const Akonadi::Collection::List addressBookCollections = addressBookJob->collections();
    for (const Akonadi::Collection &collection : addressBookCollections) {
        if (Akonadi::Collection::CanCreateItem & collection.rights()) {
            canCreateItemCollections.append(collection);
        }
    }
    Akonadi::Collection addressBook;

    const int nbItemCollection(canCreateItemCollections.size());
    if (nbItemCollection == 0) {
        if (KMessageBox::questionTwoActions(nullptr,
                                            i18nc("@info", "You must create an address book before adding a contact. Do you want to create an address book?"),
                                            i18nc("@title:window", "No Address Book Available"),
                                            KGuiItem(i18nc("@action:button", "Create Address Book"), QStringLiteral("address-book-new")),
                                            KStandardGuiItem::cancel())
            == KMessageBox::ButtonCode::PrimaryAction) {
            QPointer<Akonadi::AgentTypeDialog> dlg = new Akonadi::AgentTypeDialog(nullptr);
            dlg->setWindowTitle(i18nc("@title:window", "Add Address Book"));
            dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
            dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::ContactGroup::mimeType());
            dlg->agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

            if (dlg->exec()) {
                const Akonadi::AgentType agentType = dlg->agentType();

                if (agentType.isValid()) {
                    auto createJob = new Akonadi::AgentInstanceCreateJob(agentType, this);
                    connect(createJob, &KJob::result, this, &AutomaticAddContactsJob::slotResourceCreationDone);
                    createJob->configure();
                    createJob->start();
                    delete dlg;
                    return;
                } else { // if agent is not valid => return error and finish job
                    deleteLaterAndEmitSignal();
                    delete dlg;
                    return;
                }
            } else { // Canceled create agent => return error and finish job
                deleteLaterAndEmitSignal();
                delete dlg;
                return;
            }
        } else {
            deleteLaterAndEmitSignal();
            return;
        }
    } else if (nbItemCollection == 1) {
        addressBook = canCreateItemCollections[0];
    } else {
        // ask user in which address book the new contact shall be stored
        QPointer<Akonadi::SelectAddressBookDialog> dlg = new Akonadi::SelectAddressBookDialog(nullptr);

        bool gotIt = true;
        if (dlg->exec()) {
            addressBook = dlg->selectedCollection();
        } else {
            gotIt = false;
        }
        delete dlg;
        if (!gotIt) {
            qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to selected Addressbook selected not valid";
            deleteLaterAndEmitSignal();
            return;
        }
    }

    if (!addressBook.isValid()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Addressbook selected not valid";
        deleteLaterAndEmitSignal();
        return;
    }
    addNextContact();
}

void AutomaticAddContactsJob::slotResourceCreationDone(KJob *job)
{
    if (job->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to create resource:" << job->errorText();
        deleteLaterAndEmitSignal();
        return;
    }
    addNextContact();
}

void AutomaticAddContactsJob::verifyContactExist()
{
    const QString email = mEmails.at(mCurrentIndex);
    QString tname;
    QString temail;
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
            auto searchJob = new Akonadi::ContactSearchJob(this);
            searchJob->setLimit(1);
            searchJob->setQuery(Akonadi::ContactSearchJob::Email, mProcessEmail.toLower(), Akonadi::ContactSearchJob::ExactMatch);
            connect(searchJob, &KJob::result, this, &AutomaticAddContactsJob::slotSearchDone);
        }
    }
}

void AutomaticAddContactsJob::slotSearchDone(KJob *job)
{
    auto searchJob = static_cast<Akonadi::ContactSearchJob *>(job);
    if (searchJob->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Unable to fetch contact:" << searchJob->errorText();
    } else if (searchJob->contacts().isEmpty()) {
        KContacts::Addressee contact;
        contact.setNameFromString(mName);
        KContacts::Email email(mProcessEmail);
        email.setPreferred(true);
        contact.addEmail(email);

        // create the new item
        Akonadi::Item item;
        item.setMimeType(KContacts::Addressee::mimeType());
        item.setPayload<KContacts::Addressee>(contact);

        // save the new item in akonadi storage
        auto createJob = new Akonadi::ItemCreateJob(item, mCollection, this);
        connect(createJob, &KJob::result, this, &AutomaticAddContactsJob::slotAddContactDone);
        return;
    }
    addNextContact();
}

void AutomaticAddContactsJob::slotAddContactDone(KJob *job)
{
    if (job->error()) {
        qCWarning(KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG) << "Error when add contact to addressbook:" << job->errorText();
    }
    addNextContact();
}

void AutomaticAddContactsJob::addNextContact()
{
    mCurrentIndex++;
    if (mCurrentIndex < mEmails.count()) {
        verifyContactExist();
    } else {
        deleteLaterAndEmitSignal();
    }
}

void AutomaticAddContactsJob::setEmails(const QStringList &list)
{
    mEmails = PimCommon::Util::generateEmailList(list);
}

void AutomaticAddContactsJob::setCollection(const Akonadi::Collection &collection)
{
    mCollection = collection;
}

void AutomaticAddContactsJob::deleteLaterAndEmitSignal()
{
    Q_EMIT finished();
    deleteLater();
}
