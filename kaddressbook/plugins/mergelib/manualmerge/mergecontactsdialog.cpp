/*
    SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactsdialog.h"
#include "manualmerge/mergecontactwidget.h"
#include "widgets/mergecontacterrorlabel.h"
#include "widgets/mergecontactinfowidget.h"
#include "widgets/mergecontactselectinformationscrollarea.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;

using namespace KABMergeContacts;
namespace
{
const char myConfigGroupName[] = "MergeContactsDialog";
}
MergeContactsDialog::MergeContactsDialog(QWidget *parent)
    : QDialog(parent)
    , mButtonBox(new QDialogButtonBox(QDialogButtonBox::Close, this))
    , mStackedWidget(new QStackedWidget(this))
    , mNoEnoughContactSelected(new KABMergeContacts::MergeContactErrorLabel(KABMergeContacts::MergeContactErrorLabel::NotEnoughContactsSelected, this))
    , mNoContactSelected(new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactSelected, this))
    , mManualMergeResultWidget(new KABMergeContacts::MergeContactWidget(this))
    , mSelectInformation(new KABMergeContacts::MergeContactSelectInformationScrollArea(this))
    , mMergeContactInfo(new KABMergeContacts::MergeContactInfoWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Select Contacts to merge"));
    mButtonBox->setObjectName("buttonbox"_L1);
    auto mainLayout = new QVBoxLayout(this);
    connect(mButtonBox, &QDialogButtonBox::rejected, this, &MergeContactsDialog::reject);
    readConfig();

    mStackedWidget->setObjectName("stackedwidget"_L1);
    mainLayout->addWidget(mStackedWidget);
    mainLayout->addWidget(mButtonBox);

    mNoEnoughContactSelected->setObjectName("notenoughcontactselected"_L1);
    mStackedWidget->addWidget(mNoEnoughContactSelected);

    mNoContactSelected->setObjectName("nocontactselected"_L1);
    mStackedWidget->addWidget(mNoContactSelected);

    mManualMergeResultWidget->setObjectName("manualmergeresultwidget"_L1);
    mStackedWidget->addWidget(mManualMergeResultWidget);
    connect(mManualMergeResultWidget, &MergeContactWidget::customizeMergeContact, this, &MergeContactsDialog::slotCustomizeMergeContact);
    connect(mManualMergeResultWidget, &MergeContactWidget::contactMerged, this, &MergeContactsDialog::slotContactMerged);

    mSelectInformation->setObjectName("selectioninformation"_L1);
    mStackedWidget->addWidget(mSelectInformation);

    mMergeContactInfo->setObjectName("mergecontactinfowidget"_L1);
    mStackedWidget->addWidget(mMergeContactInfo);

    mStackedWidget->setCurrentWidget(mNoContactSelected);
}

MergeContactsDialog::~MergeContactsDialog()
{
    writeConfig();
}

void MergeContactsDialog::setContacts(const Akonadi::Item::List &list)
{
    if (list.isEmpty()) {
        mStackedWidget->setCurrentWidget(mNoContactSelected);
    } else if (list.count() < 2) {
        mStackedWidget->setCurrentWidget(mNoEnoughContactSelected);
    } else {
        mManualMergeResultWidget->setContacts(list);
        mStackedWidget->setCurrentWidget(mManualMergeResultWidget);
    }
    mButtonBox->button(QDialogButtonBox::Close)->setEnabled(true);
}

void MergeContactsDialog::slotCustomizeMergeContact(const Akonadi::Item::List &lst,
                                                    MergeContacts::ConflictInformations conflictType,
                                                    const Akonadi::Collection &col)
{
    mSelectInformation->setContacts(conflictType, lst, col);
    mStackedWidget->setCurrentWidget(mSelectInformation);
}

void MergeContactsDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigGroupName), 300, 200);
}

void MergeContactsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

void MergeContactsDialog::slotContactMerged(const Akonadi::Item &item)
{
    mMergeContactInfo->setContact(item);
    mStackedWidget->setCurrentWidget(mMergeContactInfo);
}

#include "moc_mergecontactsdialog.cpp"
