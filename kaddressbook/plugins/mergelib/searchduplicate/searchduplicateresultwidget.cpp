/*
    Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "searchduplicateresultwidget.h"
#include "widgets/mergecontactloseinformationwarning.h"
#include "job/mergecontactsjob.h"
#include "job/mergecontacts.h"

#include "resultduplicatetreewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include "KaddressbookGrantlee/GrantleeContactViewer"
#include <AkonadiWidgets/CollectionComboBox>

namespace KABMergeContacts {
KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_searchDuplicateResultStubModel = nullptr;
}

using namespace KABMergeContacts;
SearchDuplicateResultWidget::SearchDuplicateResultWidget(QWidget *parent)
    : QWidget(parent)
    , mIndexListContact(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

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
    connect(mCollectionCombobox, QOverload<int>::of(&Akonadi::CollectionComboBox::currentIndexChanged), this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
    connect(mCollectionCombobox, QOverload<int>::of(&Akonadi::CollectionComboBox::activated), this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
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
        if (!conflictFound) {
            //Detect if conflict.
            mergeContact();
        } else {
            mMergeContactWarning->animatedShow();
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
