/*
    SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

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

#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWindow>

using namespace KABMergeContacts;
namespace
{
static const char mySearchAndMergeContactDuplicateContactDialogGroupName[] = "SearchAndMergeContactDuplicateContactDialog";
}
SearchAndMergeContactDuplicateContactDialog::SearchAndMergeContactDuplicateContactDialog(QWidget *parent)
    : QDialog(parent)
    , mSearchResult(new SearchDuplicateResultWidget(this))
    , mMergeContactResult(new MergeContactShowResultTabWidget(this))
    , mNoContactSelected(new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactSelected, this))
    , mNoDuplicateContactFound(new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactDuplicatesFound, this))
    , mNoEnoughContactSelected(new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NotEnoughContactsSelected, this))
    , mSelectInformation(new KABMergeContacts::MergeContactSelectInformationTabWidget(this))
    , mStackedWidget(new QStackedWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Search and Select Duplicate Contacts to merge"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    auto mainLayout = new QVBoxLayout(this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SearchAndMergeContactDuplicateContactDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SearchAndMergeContactDuplicateContactDialog::reject);
    mStackedWidget->setObjectName(QLatin1StringView("stackedwidget"));

    mSearchResult->setObjectName(QLatin1StringView("mergecontact"));
    mStackedWidget->addWidget(mSearchResult);
    connect(mSearchResult, &SearchDuplicateResultWidget::contactMerged, this, &SearchAndMergeContactDuplicateContactDialog::slotContactMerged);
    connect(mSearchResult, &SearchDuplicateResultWidget::mergeDone, this, &SearchAndMergeContactDuplicateContactDialog::slotMergeDone);
    connect(mSearchResult, &SearchDuplicateResultWidget::customizeMergeContact, this, &SearchAndMergeContactDuplicateContactDialog::slotCustomizeMergeContacts);

    mNoContactSelected->setObjectName(QLatin1StringView("nocontactselected"));
    mStackedWidget->addWidget(mNoContactSelected);

    mNoDuplicateContactFound->setObjectName(QLatin1StringView("nocontactduplicatesfound"));
    mStackedWidget->addWidget(mNoDuplicateContactFound);

    mMergeContactResult->setObjectName(QLatin1StringView("mergecontactresult"));
    mStackedWidget->addWidget(mMergeContactResult);

    mNoEnoughContactSelected->setObjectName(QLatin1StringView("noenoughcontactselected"));
    mStackedWidget->addWidget(mNoEnoughContactSelected);
    mStackedWidget->setCurrentWidget(mNoContactSelected);

    mSelectInformation->setObjectName(QLatin1StringView("selectioninformation"));
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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(mySearchAndMergeContactDuplicateContactDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void SearchAndMergeContactDuplicateContactDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(mySearchAndMergeContactDuplicateContactDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

void SearchAndMergeContactDuplicateContactDialog::slotDuplicateFound(const QList<Akonadi::Item::List> &duplicate)
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

void SearchAndMergeContactDuplicateContactDialog::slotCustomizeMergeContacts(const QList<MergeConflictResult> &lst, const Akonadi::Collection &col)
{
    mSelectInformation->setRequiresSelectInformationWidgets(lst, col);
    mStackedWidget->setCurrentWidget(mSelectInformation);
}

#include "moc_searchandmergecontactduplicatecontactdialog.cpp"
