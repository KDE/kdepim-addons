/*
    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactsdialog.h"
#include "job/mergecontactsjob.h"
#include "manualmerge/mergecontactwidget.h"
#include "widgets/mergecontacterrorlabel.h"
#include "widgets/mergecontactinfowidget.h"
#include "widgets/mergecontactselectinformationscrollarea.h"

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
static const char myConfigGroupName[] = "MergeContactsDialog";
}
MergeContactsDialog::MergeContactsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Select Contacts to merge"));
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    mButtonBox->setObjectName(QStringLiteral("buttonbox"));
    auto mainLayout = new QVBoxLayout(this);
    connect(mButtonBox, &QDialogButtonBox::rejected, this, &MergeContactsDialog::reject);
    readConfig();

    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));
    mainLayout->addWidget(mStackedWidget);
    mainLayout->addWidget(mButtonBox);

    mNoEnoughContactSelected = new KABMergeContacts::MergeContactErrorLabel(KABMergeContacts::MergeContactErrorLabel::NotEnoughContactsSelected);
    mNoEnoughContactSelected->setObjectName(QStringLiteral("notenoughcontactselected"));
    mStackedWidget->addWidget(mNoEnoughContactSelected);

    mNoContactSelected = new KABMergeContacts::MergeContactErrorLabel(MergeContactErrorLabel::NoContactSelected, this);
    mNoContactSelected->setObjectName(QStringLiteral("nocontactselected"));
    mStackedWidget->addWidget(mNoContactSelected);

    mManualMergeResultWidget = new KABMergeContacts::MergeContactWidget(this);
    mManualMergeResultWidget->setObjectName(QStringLiteral("manualmergeresultwidget"));
    mStackedWidget->addWidget(mManualMergeResultWidget);
    connect(mManualMergeResultWidget, &MergeContactWidget::customizeMergeContact, this, &MergeContactsDialog::slotCustomizeMergeContact);
    connect(mManualMergeResultWidget, &MergeContactWidget::contactMerged, this, &MergeContactsDialog::slotContactMerged);

    mSelectInformation = new KABMergeContacts::MergeContactSelectInformationScrollArea(this);
    mSelectInformation->setObjectName(QStringLiteral("selectioninformation"));
    mStackedWidget->addWidget(mSelectInformation);

    mMergeContactInfo = new KABMergeContacts::MergeContactInfoWidget;
    mMergeContactInfo->setObjectName(QStringLiteral("mergecontactinfowidget"));
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
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void MergeContactsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}

void MergeContactsDialog::slotContactMerged(const Akonadi::Item &item)
{
    mMergeContactInfo->setContact(item);
    mStackedWidget->setCurrentWidget(mMergeContactInfo);
}
