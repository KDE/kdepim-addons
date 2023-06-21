/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "searchduplicateresultwidget.h"
#include "job/mergecontactsjob.h"
#include "widgets/mergecontactloseinformationwarning.h"

#include "resultduplicatetreewidget.h"
#include <Akonadi/CollectionComboBox>
#include <Akonadi/GrantleeContactViewer>
#include <KLocalizedString>
#include <KTreeWidgetSearchLine>
#include <KTreeWidgetSearchLineWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>

namespace KABMergeContacts
{
KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_searchDuplicateResultStubModel = nullptr;
}

using namespace KABMergeContacts;
SearchDuplicateResultWidget::SearchDuplicateResultWidget(QWidget *parent)
    : QWidget(parent)
    , mResultTreeWidget(new ResultDuplicateTreeWidget(this))
    , mContactViewer(new KAddressBookGrantlee::GrantleeContactViewer(this))
    , mMergeContactWarning(new MergeContactLoseInformationWarning(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});

    auto splitter = new QSplitter;
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);
    mainLayout->addWidget(splitter);
    mResultTreeWidget->setObjectName(QStringLiteral("result_treewidget"));
    mContactViewer->setObjectName(QStringLiteral("contact_viewer"));

    mSearchInResultLineEdit = new KTreeWidgetSearchLineWidget(this, mResultTreeWidget);
    mSearchInResultLineEdit->setObjectName(QStringLiteral("searchinresultlineedit"));
    mSearchInResultLineEdit->searchLine()->setClearButtonEnabled(true);
    mSearchInResultLineEdit->searchLine()->setPlaceholderText(i18n("Search in result..."));

    auto resultWidget = new QWidget(this);
    auto resultWidgetLayout = new QVBoxLayout(resultWidget);
    resultWidgetLayout->setContentsMargins({});
    resultWidgetLayout->addWidget(mSearchInResultLineEdit);
    resultWidgetLayout->addWidget(mResultTreeWidget);
    splitter->addWidget(resultWidget);
    splitter->addWidget(mContactViewer);
    connect(mResultTreeWidget, &ResultDuplicateTreeWidget::showContactPreview, mContactViewer, &KAddressBookGrantlee::GrantleeContactViewer::setContact);
    connect(mResultTreeWidget, &ResultDuplicateTreeWidget::customContextMenuRequested, this, &SearchDuplicateResultWidget::slotCustomContextMenuRequested);

    mMergeContactWarning->setObjectName(QStringLiteral("mergecontactwarning"));
    connect(mMergeContactWarning, &MergeContactLoseInformationWarning::continueMerging, this, &SearchDuplicateResultWidget::slotAutomaticMerging);
    connect(mMergeContactWarning,
            &MergeContactLoseInformationWarning::customizeMergingContacts,
            this,
            &SearchDuplicateResultWidget::slotCustomizeMergingContacts);
    mainLayout->addWidget(mMergeContactWarning);

    auto mergeLayout = new QHBoxLayout;
    mainLayout->addLayout(mergeLayout);
    mergeLayout->addStretch();

    auto lab = new QLabel(i18n("Select AddressBook:"));
    lab->setObjectName(QStringLiteral("select_addressbook_label"));
    mergeLayout->addWidget(lab);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_searchDuplicateResultStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
    mCollectionCombobox->setObjectName(QStringLiteral("akonadicombobox"));
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &SearchDuplicateResultWidget::slotUpdateMergeButton);
    mergeLayout->addWidget(mCollectionCombobox);

    mMergeContact = new QPushButton(i18n("Merge"), this);
    mMergeContact->setObjectName(QStringLiteral("merge_contact_button"));
    connect(mMergeContact, &QPushButton::clicked, this, &SearchDuplicateResultWidget::slotMergeContact);
    mergeLayout->addWidget(mMergeContact);
    mMergeContact->setEnabled(false);
    // TODO make mMergeContact enable when selected item and collection valid
}

SearchDuplicateResultWidget::~SearchDuplicateResultWidget() = default;

void SearchDuplicateResultWidget::slotCustomContextMenuRequested(const QPoint &)
{
    QMenu menu(this);
    menu.addAction(i18n("Expand All"), this, &SearchDuplicateResultWidget::slotExpandAll);
    menu.addAction(i18n("Collapse All"), this, &SearchDuplicateResultWidget::slotCollapseAll);
    menu.addSeparator();
    menu.addAction(i18n("Select All"), this, &SearchDuplicateResultWidget::slotSelectAll);
    menu.addAction(i18n("Deselect All"), this, &SearchDuplicateResultWidget::slotDeselectAll);
    menu.exec(QCursor::pos());
}

void SearchDuplicateResultWidget::slotExpandAll()
{
    mResultTreeWidget->expandAll();
}

void SearchDuplicateResultWidget::slotCollapseAll()
{
    mResultTreeWidget->collapseAll();
}

void SearchDuplicateResultWidget::slotSelectAll()
{
    mResultTreeWidget->checkAllItems();
}

void SearchDuplicateResultWidget::slotDeselectAll()
{
    mResultTreeWidget->uncheckAllItems();
}

void SearchDuplicateResultWidget::setContacts(const QList<Akonadi::Item::List> &lstItem)
{
    mResultTreeWidget->setContacts(lstItem);
}

void SearchDuplicateResultWidget::slotMergeContact()
{
    mIndexListContact = 0;
    mListContactToMerge = mResultTreeWidget->selectedContactsToMerge();
    if (!mListContactToMerge.isEmpty()) {
        KABMergeContacts::MergeContacts mergeContacts;
        bool conflictFound = false;
        mResultConflictList.clear();
        for (const Akonadi::Item::List &lst : std::as_const(mListContactToMerge)) {
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
            // Detect if conflict.
            mergeContact();
        }
    }
}

void SearchDuplicateResultWidget::mergeContact()
{
    if (mIndexListContact < mListContactToMerge.count()) {
        auto job = new KABMergeContacts::MergeContactsJob(this);
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

#include "moc_searchduplicateresultwidget.cpp"
