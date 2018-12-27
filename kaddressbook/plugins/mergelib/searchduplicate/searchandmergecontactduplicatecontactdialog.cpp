/*
    Copyright (c) 2014-2019 Montel Laurent <montel@kde.org>

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

#include "searchandmergecontactduplicatecontactdialog.h"

#include "mergecontactselectinformationtabwidget.h"
#include "searchduplicate/searchduplicateresultwidget.h"
#include "widgets/mergecontactshowresulttabwidget.h"
#include "widgets/mergecontacterrorlabel.h"
#include "job/searchpotentialduplicatecontactjob.h"

#include <KLocalizedString>
#include <KSharedConfig>
#include <KConfigGroup>

#include <QStackedWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace KABMergeContacts;

SearchAndMergeContactDuplicateContactDialog::SearchAndMergeContactDuplicateContactDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Search and Select Duplicate Contacts to merge"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SearchAndMergeContactDuplicateContactDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SearchAndMergeContactDuplicateContactDialog::reject);
    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));

    mSearchResult = new SearchDuplicateResultWidget;
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
    const int listCount {
        list.count()
    };
    if (listCount == 0) {
        mStackedWidget->setCurrentWidget(mNoContactSelected);
    } else if (listCount < 2) {
        mStackedWidget->setCurrentWidget(mNoEnoughContactSelected);
    } else {
        SearchPotentialDuplicateContactJob *job = new SearchPotentialDuplicateContactJob(list, this);
        connect(job, &SearchPotentialDuplicateContactJob::finished, this, &SearchAndMergeContactDuplicateContactDialog::slotDuplicateFound);
        job->start();
    }
}

void SearchAndMergeContactDuplicateContactDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "MergeContactDuplicateContactDialog");
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void SearchAndMergeContactDuplicateContactDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "MergeContactDuplicateContactDialog");
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
