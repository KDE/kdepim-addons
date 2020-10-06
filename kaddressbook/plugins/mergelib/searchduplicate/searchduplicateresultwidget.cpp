/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "searchduplicateresultwidget.h"
#include "widgets/mergecontactloseinformationwarning.h"
#include "job/mergecontactsjob.h"
#include "job/mergecontacts.h"

#include "resultduplicatetreewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include <Akonadi/Contact/GrantleeContactViewer>
#include <AkonadiWidgets/CollectionComboBox>

namespace KABMergeContacts {
KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_searchDuplicateResultStubModel = nullptr;
}

using namespace KABMergeContacts;
SearchDuplicateResultWidget::SearchDuplicateResultWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});

    QSplitter *splitter = new QSplitter;
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);
    mainLayout->addWidget(splitter);
    mResult = new ResultDuplicateTreeWidget;
    mResult->setObjectName(QStringLiteral("result_treewidget"));
    mContactViewer = new KAddressBookGrantlee::GrantleeContactViewer;
    mContactViewer->setObjectName(QStringLiteral("contact_viewer"));
    splitter->addWidget(mResult);
    splitter->addWidget(mContactViewer);
    connect(mResult, &ResultDuplicateTreeWidget::showContactPreview, mContactViewer, &KAddressBookGrantlee::GrantleeContactViewer::setContact);

    mMergeContactWarning = new MergeContactLoseInformationWarning;
    mMergeContactWarning->setObjectName(QStringLiteral("mergecontactwarning"));
    connect(mMergeContactWarning, &MergeContactLoseInformationWarning::continueMerging, this, &SearchDuplicateResultWidget::slotAutomaticMerging);
    connect(mMergeContactWarning, &MergeContactLoseInformationWarning::customizeMergingContacts, this, &SearchDuplicateResultWidget::slotCustomizeMergingContacts);
    mainLayout->addWidget(mMergeContactWarning);

    QHBoxLayout *mergeLayout = new QHBoxLayout;
    mainLayout->addLayout(mergeLayout);
    mergeLayout->addStretch();

    QLabel *lab = new QLabel(i18n("Select AddressBook:"));
    lab->setObjectName(QStringLiteral("select_addressbook_label"));
    mergeLayout->addWidget(lab);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_searchDuplicateResultStubModel);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
    mCollectionCombobox->setObjectName(QStringLiteral("akonadicombobox"));
    connect(mCollectionCombobox, qOverload<int>(&Akonadi::CollectionComboBox::currentIndexChanged), this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
    connect(mCollectionCombobox, qOverload<int>(&Akonadi::CollectionComboBox::activated), this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
    mergeLayout->addWidget(mCollectionCombobox);

    mMergeContact = new QPushButton(i18n("Merge"));
    mMergeContact->setObjectName(QStringLiteral("merge_contact_button"));
    connect(mMergeContact, &QPushButton::clicked, this, &SearchDuplicateResultWidget::slotMergeContact);
    mergeLayout->addWidget(mMergeContact);
    mMergeContact->setEnabled(false);
    //TODO make mMergeContact enable when selected item and collection valid
}

SearchDuplicateResultWidget::~SearchDuplicateResultWidget()
{
}

void SearchDuplicateResultWidget::setContacts(const QVector<Akonadi::Item::List> &lstItem)
{
    mResult->setContacts(lstItem);
}

void SearchDuplicateResultWidget::slotMergeContact()
{
    mIndexListContact = 0;
    mListContactToMerge = mResult->selectedContactsToMerge();
    if (!mListContactToMerge.isEmpty()) {
        KABMergeContacts::MergeContacts mergeContacts;
        bool conflictFound = false;
        mResultConflictList.clear();
        for (const Akonadi::Item::List &lst : qAsConst(mListContactToMerge)) {
            mergeContacts.setItems(lst);
            const MergeContacts::ConflictInformations conflicts = mergeContacts.requiresManualSelectionOfInformation();
            if (conflicts != MergeContacts::None) {
                conflictFound = true;
            }
            MergeConflictResult result;
            result.list = lst;
            result.conflictInformation = conflicts;
            mResultConflictList.append(result);
        }

        mMergeContact->setEnabled(false);
        if (conflictFound) {
            mMergeContactWarning->animatedShow();
        } else {
            //Detect if conflict.
            mergeContact();
        }
    }
}

void SearchDuplicateResultWidget::mergeContact()
{
    if (mIndexListContact < mListContactToMerge.count()) {
        KABMergeContacts::MergeContactsJob *job = new KABMergeContacts::MergeContactsJob(this);
        job->setListItem(mListContactToMerge.at(mIndexListContact));
        job->setDestination(mCollectionCombobox->currentCollection());
        connect(job, &KABMergeContacts::MergeContactsJob::finished, this, &SearchDuplicateResultWidget::slotMergeDone);
        job->start();
    } else {
        Q_EMIT mergeDone();
    }
}

void SearchDuplicateResultWidget::slotMergeDone(const Akonadi::Item &item)
{
    ++mIndexListContact;
    Q_EMIT contactMerged(item);
    mergeContact();
}

void SearchDuplicateResultWidget::slotUpdateMergeButton()
{
    mMergeContact->setEnabled(mCollectionCombobox->currentCollection().isValid());
}

void SearchDuplicateResultWidget::slotAutomaticMerging()
{
    mergeContact();
}

void SearchDuplicateResultWidget::slotCustomizeMergingContacts()
{
    Q_EMIT customizeMergeContact(mResultConflictList, mCollectionCombobox->currentCollection());
}
