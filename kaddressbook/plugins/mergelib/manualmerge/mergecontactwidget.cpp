/*
    SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactwidget.h"
#include "mergecontactwidgetlist.h"

#include <KLocalizedString>
#include <QSplitter>

#include "job/mergecontactsjob.h"
#include "widgets/mergecontactinfowidget.h"
#include "widgets/mergecontactloseinformationwarning.h"
#include <Akonadi/CollectionComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace KABMergeContacts
{
KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_mergeStubModel = nullptr;
}

using namespace KABMergeContacts;
MergeContactWidget::MergeContactWidget(QWidget *parent)
    : QWidget(parent)
    , mConflictTypes(MergeContacts::None)
    , mListWidget(new MergeContactWidgetList(this))
    , mMergeButton(new QPushButton(i18nc("@action:button", "merge"), this))
    , mMergeContactWarning(new MergeContactLoseInformationWarning(this))
    , mMergeContactInfoWidget(new MergeContactInfoWidget(this))
{
    auto lay = new QVBoxLayout(this);
    lay->setContentsMargins({});

    auto splitter = new QSplitter;
    splitter->setObjectName(QLatin1StringView("splitter"));
    splitter->setChildrenCollapsible(false);
    lay->addWidget(splitter);

    auto selectContactWidget = new QWidget(this);
    selectContactWidget->setObjectName(QLatin1StringView("selectcontactwidget"));
    auto vbox = new QVBoxLayout;
    selectContactWidget->setLayout(vbox);
    auto lab = new QLabel(i18nc("@label:textbox", "Select contacts that you really want to merge:"), this);
    vbox->addWidget(lab);
    mListWidget->setObjectName(QLatin1StringView("listcontact"));
    mListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    vbox->addWidget(mListWidget);
    connect(mListWidget, &MergeContactWidgetList::itemSelectionChanged, this, &MergeContactWidget::slotUpdateMergeButton);
    connect(mListWidget, &MergeContactWidgetList::itemChanged, this, &MergeContactWidget::slotUpdateMergeButton);
    splitter->addWidget(selectContactWidget);

    mMergeContactInfoWidget->setObjectName(QLatin1StringView("mergecontactinfowidget"));
    splitter->addWidget(mMergeContactInfoWidget);

    mMergeContactWarning->setObjectName(QLatin1StringView("mergecontactwarning"));
    connect(mMergeContactWarning, &MergeContactLoseInformationWarning::continueMerging, this, &MergeContactWidget::slotAutomaticMerging);
    connect(mMergeContactWarning, &MergeContactLoseInformationWarning::customizeMergingContacts, this, &MergeContactWidget::slotCustomizeMergingContacts);
    lay->addWidget(mMergeContactWarning);

    auto hbox = new QHBoxLayout;
    hbox->addStretch();

    lab = new QLabel(i18nc("@label:textbox", "Select the addressbook in which to store merged contacts:"));
    hbox->addWidget(lab);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_mergeStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
    mCollectionCombobox->setObjectName(QLatin1StringView("akonadicombobox"));
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &MergeContactWidget::slotUpdateMergeButton);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &MergeContactWidget::slotUpdateMergeButton);

    hbox->addWidget(mCollectionCombobox);

    lay->addLayout(hbox);

    mMergeButton->setObjectName(QLatin1StringView("mergebutton"));
    hbox->addWidget(mMergeButton);
    mMergeButton->setEnabled(false);

    connect(mMergeButton, &QPushButton::clicked, this, &MergeContactWidget::slotMergeContacts);
}

MergeContactWidget::~MergeContactWidget() = default;

void MergeContactWidget::setContacts(const Akonadi::Item::List &items)
{
    mItems = items;
    mListWidget->fillListContact(mItems);
}

Akonadi::Item::List MergeContactWidget::listSelectedContacts() const
{
    return mListWidget->listSelectedContacts();
}

Akonadi::Item MergeContactWidget::currentItem() const
{
    return mListWidget->currentAkonadiItem();
}

void MergeContactWidget::slotUpdateMergeButton()
{
    const Akonadi::Item::List listCheckedItems = listSelectedContacts();
    Akonadi::Item item = currentItem();
    mMergeContactInfoWidget->setContact(item);
    mMergeButton->setEnabled((listCheckedItems.count() >= 2) && mCollectionCombobox->currentCollection().isValid());
}

void MergeContactWidget::slotMergeContacts()
{
    mSelectedItems = listSelectedContacts();
    // const Akonadi::Collection col = mCollectionCombobox->currentCollection();

    KABMergeContacts::MergeContacts mergeContacts;
    mergeContacts.setItems(mSelectedItems);
    mConflictTypes = mergeContacts.requiresManualSelectionOfInformation();
    if (mConflictTypes != MergeContacts::None) {
        mMergeContactWarning->animatedShow();
    } else {
        slotAutomaticMerging();
    }
}

void MergeContactWidget::slotAutomaticMerging()
{
    auto job = new KABMergeContacts::MergeContactsJob(this);
    job->setListItem(mSelectedItems);
    job->setDestination(mCollectionCombobox->currentCollection());
    connect(job, &MergeContactsJob::finished, this, &MergeContactWidget::slotMergeDone);
    job->start();
}

void MergeContactWidget::slotCustomizeMergingContacts()
{
    Q_EMIT customizeMergeContact(mSelectedItems, mConflictTypes, mCollectionCombobox->currentCollection());
}

void MergeContactWidget::slotMergeDone(const Akonadi::Item &item)
{
    Q_EMIT contactMerged(item);
}

#include "moc_mergecontactwidget.cpp"
