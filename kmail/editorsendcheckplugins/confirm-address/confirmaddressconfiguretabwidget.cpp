/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmaddresssimplestringlisteditor.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>

ConfirmAddressConfigureTabWidget::ConfirmAddressConfigureTabWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    mainLayout->setContentsMargins({});

    auto groupBoxDomainName = new QGroupBox(this);
    groupBoxDomainName->setObjectName("groupboxdomainname"_L1);
    mainLayout->addWidget(groupBoxDomainName);
    auto layoutDomainName = new QVBoxLayout(groupBoxDomainName);
    layoutDomainName->setObjectName("layoutdomainname"_L1);

    auto radioButtonLayout = new QHBoxLayout;
    layoutDomainName->addLayout(radioButtonLayout);
    radioButtonLayout->setAlignment(Qt::AlignHCenter);

    mAcceptedDomain = new QRadioButton(i18nc("@option:radio", "Accepted Domain Name"), this);
    mAcceptedDomain->setObjectName("acceptdomainname"_L1);
    radioButtonLayout->addWidget(mAcceptedDomain);
    mAcceptedDomain->setChecked(true);

    mRejectedDomain = new QRadioButton(i18nc("@option:radio", "Rejected Domain Name"), this);
    mRejectedDomain->setObjectName("rejectdomainname"_L1);
    radioButtonLayout->addWidget(mRejectedDomain);

    auto buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(
        PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mDomainNameListEditor = new ConfirmAddressSimpleStringListEditor(groupBoxDomainName,
                                                                     buttonCode,
                                                                     i18n("A&dd…"),
                                                                     i18n("Re&move"),
                                                                     i18n("Mod&ify…"),
                                                                     i18n("Enter new domain name:"));
    mDomainNameListEditor->setObjectName("domainnamelisteditor"_L1);
    mDomainNameListEditor->setRemoveDialogLabel(i18n("Do you want to remove this domain?"));
    connect(mDomainNameListEditor, &ConfirmAddressSimpleStringListEditor::changed, this, &ConfirmAddressConfigureTabWidget::configureChanged);
    layoutDomainName->addWidget(mDomainNameListEditor);

    auto groupBoxWhiteList = new QGroupBox(i18n("Whitelist of Addresses"), this);
    groupBoxWhiteList->setObjectName("groupboxwhitelist"_L1);
    mainLayout->addWidget(groupBoxWhiteList);
    auto layoutWhiteList = new QVBoxLayout(groupBoxWhiteList);
    layoutWhiteList->setObjectName("layoutwhitelist"_L1);

    buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove
                                                                            | PimCommon::SimpleStringListEditor::Modify);
    mWhiteListEditor = new ConfirmAddressSimpleStringListEditor(groupBoxWhiteList,
                                                                buttonCode,
                                                                i18n("A&dd…"),
                                                                i18n("Re&move"),
                                                                i18n("Mod&ify…"),
                                                                i18n("Enter new email address:"));
    mWhiteListEditor->setObjectName("whitelisteditor"_L1);
    mWhiteListEditor->setRemoveDialogLabel(i18n("Do you want to remove this email address?"));
    layoutWhiteList->addWidget(mWhiteListEditor);
    connect(mWhiteListEditor, &ConfirmAddressSimpleStringListEditor::changed, this, &ConfirmAddressConfigureTabWidget::configureChanged);
}

ConfirmAddressConfigureTabWidget::~ConfirmAddressConfigureTabWidget() = default;

void ConfirmAddressConfigureTabWidget::resetSettings()
{
    mDomainNameListEditor->setStringList({});
    mWhiteListEditor->setStringList({});
    mAcceptedDomain->setChecked(true);
}

void ConfirmAddressConfigureTabWidget::loadSettings(const KConfigGroup &grp)
{
    KConfigGroup identityGroup = grp.group(u"Confirm Address %1"_s.arg(mIdentity));
    mDomainNameListEditor->setStringList(identityGroup.readEntry("Domains", QStringList()));
    mWhiteListEditor->setStringList(identityGroup.readEntry("Emails", QStringList()));
    const bool rejectedDomain = identityGroup.readEntry("RejectDomain", false);
    if (rejectedDomain) {
        mRejectedDomain->setChecked(true);
    } else {
        mAcceptedDomain->setChecked(true);
    }
}

void ConfirmAddressConfigureTabWidget::saveSettings(KConfigGroup &grp)
{
    KConfigGroup identityGroup = grp.group(u"Confirm Address %1"_s.arg(mIdentity));
    identityGroup.writeEntry("Domains", mDomainNameListEditor->stringList());
    identityGroup.writeEntry("Emails", mWhiteListEditor->stringList());
    identityGroup.writeEntry("RejectDomain", mRejectedDomain->isChecked());
}

void ConfirmAddressConfigureTabWidget::setIdentity(uint identity)
{
    mIdentity = identity;
}

#include "moc_confirmaddressconfiguretabwidget.cpp"
