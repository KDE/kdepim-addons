/*
    SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "searchandmergecontactduplicatecontactdialog.h"

#include "job/searchpotentialduplicatecontactjob.h"
#include "mergecontactselectinformationtabwidget.h"
#include "searchduplicate/searchduplicateresultwidget.h"
#include "widgets/mergecontacterrorlabel.h"
#include "widgets/mergecontactshowresulttabwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace KABMergeContacts;
namespace
{
static const char mySearchAndMergeContactDuplicateContactDialogGroupName[] = "SearchAndMergeContactDuplicateContactDialog";
}
SearchAndMergeContactDuplicateContactDialog::SearchAndMergeContactDuplicateContactDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Search and Select Duplicate Contacts to merge"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    auto mainLayout = new QVBoxLayout(this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SearchAndMergeContactDuplicateContactDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SearchAndMergeContactDuplicateContactDialog::reject);
    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));

    mSearchResult = new SearchDuplicateResultWidget(this);
    mSearchResult->setObjectName(QStringLiteral("mergecontact"));
    mStackedWidget->addWidget(mSearchResult);
    connect(mSearchResult, &SearchDuplicateResultWidget::contactMerged, this, &SearchAndMergeContactDuplicateContactDialog::slotContactMerged);
    connect(mSearchResult, &SearchDuplicateResultWidget::mergeDone, this, &SearchAndMergeContactDuplicateContactDialog::slotMergeDone);
    connect(mSearchResult, &SearchDuplicateResultWidget::customizeMergeContact, this, &SearchAndMergeContactDuplicateContactDialog::slotCustomizeMergeContacts);

    mNoContactSelected = new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactSelected, this);
    mNoContactSelected->setObjectName(QStringLiteral("nocontactselected"));
    mStackedWidget->addWidget(mNoContactSelected);

    mNoDuplicateContactFound = new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactDuplicatesFound, this);
    mNoDuplicateContactFound->setObjectName(QStringLiteral("nocontactduplicatesfound"));
    mStackedWidget->addWidget(mNoDuplicateContactFound);

    mMergeContactResult = new MergeContactShowResultTabWidget(this);
    mMergeContactResult->setObjectName(QStringLiteral("mergecontactresult"));
    mStackedWidget->addWidget(mMergeContactResult);

    mNoEnoughContactSelected = new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NotEnoughContactsSelected, this);
    mNoEnoughContactSelected->setObjectName(QStringLiteral("noenoughcontactselected"));
    mStackedWidget->addWidget(mNoEnoughContactSelected);
    mStackedWidget->setCurrentWidget(mNoContactSelected);

    mSelectInformation = new KABMergeContacts::MergeContactSelectInformationTabWidget(this);
    mSelectInformation->setObjectName(QStringLiteral("selectioninformation"));
    mStackedWidget->addWidget(mSelectInformation);

    mainLayout->addWidget(mStackedWidget);
    mainLayout->addWidget(buttonBox);

    readConfig();
}

SearchAndMergeContactDuplicateContactDialog::~SearchAndMergeContactDuplicateContactDialog()
{
    writeConfig();
}

void SearchAndMergeContactDuplicateContactDialog::searchPotentialDuplicateContacts(const Akonadi::Item::List &list)
{
    const auto listCount{list.count()};
    if (listCount == 0) {
        mStackedWidget->setCurrentWidget(mNoContactSelected);
    } else if (listCount < 2) {
        mStackedWidget->setCurrentWidget(mNoEnoughContactSelected);
    } else {
        auto job = new SearchPotentialDuplicateContactJob(list, this);
        connect(job, &SearchPotentialDuplicateContactJob::finished, this, &SearchAndMergeContactDuplicateContactDialog::slotDuplicateFound);
        job->start();
    }
}

void SearchAndMergeContactDuplicateContactDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), mySearchAndMergeContactDuplicateContactDialogGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void SearchAndMergeContactDuplicateContactDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), mySearchAndMergeContactDuplicateContactDialogGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}

void SearchAndMergeContactDuplicateContactDialog::slotDuplicateFound(const QVector<Akonadi::Item::List> &duplicate)
{
    if (duplicate.isEmpty()) {
        mStackedWidget->setCurrentWidget(mNoDuplicateContactFound);
    } else {
        mStackedWidget->setCurrentWidget(mSearchResult);
        mSearchResult->setContacts(duplicate);
    }
}

void SearchAndMergeContactDuplicateContactDialog::slotContactMerged(const Akonadi::Item &item)
{
    mMergeContactResult->addMergedContact(item, true);
}

void SearchAndMergeContactDuplicateContactDialog::slotMergeDone()
{
    mStackedWidget->setCurrentWidget(mMergeContactResult);
}

void SearchAndMergeContactDuplicateContactDialog::slotCustomizeMergeContacts(const QVector<MergeConflictResult> &lst, const Akonadi::Collection &col)
{
    mSelectInformation->setRequiresSelectInformationWidgets(lst, col);
    mStackedWidget->setCurrentWidget(mSelectInformation);
}
