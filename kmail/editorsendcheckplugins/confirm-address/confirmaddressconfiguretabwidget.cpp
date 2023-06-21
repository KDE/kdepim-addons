/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabwidget.h"
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
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    auto groupBoxDomainName = new QGroupBox(this);
    groupBoxDomainName->setObjectName(QStringLiteral("groupboxdomainname"));
    mainLayout->addWidget(groupBoxDomainName);
    auto layoutDomainName = new QVBoxLayout(groupBoxDomainName);
    layoutDomainName->setObjectName(QStringLiteral("layoutdomainname"));

    auto radioButtonLayout = new QHBoxLayout;
    layoutDomainName->addLayout(radioButtonLayout);
    radioButtonLayout->setAlignment(Qt::AlignHCenter);

    mAcceptedDomain = new QRadioButton(i18n("Accepted Domain Name"), this);
    mAcceptedDomain->setObjectName(QStringLiteral("acceptdomainname"));
    radioButtonLayout->addWidget(mAcceptedDomain);
    mAcceptedDomain->setChecked(true);

    mRejectedDomain = new QRadioButton(i18n("Rejected Domain Name"), this);
    mRejectedDomain->setObjectName(QStringLiteral("rejectdomainname"));
    radioButtonLayout->addWidget(mRejectedDomain);

    auto buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(
        PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mDomainNameListEditor = new ConfirmAddressSimpleStringListEditor(groupBoxDomainName,
                                                                     buttonCode,
                                                                     i18n("A&dd..."),
                                                                     i18n("Re&move"),
                                                                     i18n("Mod&ify..."),
                                                                     i18n("Enter new domain name:"));
    mDomainNameListEditor->setObjectName(QStringLiteral("domainnamelisteditor"));
    mDomainNameListEditor->setRemoveDialogLabel(i18n("Do you want to remove this domain?"));
    connect(mDomainNameListEditor, &ConfirmAddressSimpleStringListEditor::changed, this, &ConfirmAddressConfigureTabWidget::configureChanged);
    layoutDomainName->addWidget(mDomainNameListEditor);

    auto groupBoxWhiteList = new QGroupBox(i18n("Whitelist of Addresses"), this);
    groupBoxWhiteList->setObjectName(QStringLiteral("groupboxwhitelist"));
    mainLayout->addWidget(groupBoxWhiteList);
    auto layoutWhiteList = new QVBoxLayout(groupBoxWhiteList);
    layoutWhiteList->setObjectName(QStringLiteral("layoutwhitelist"));

    buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove
                                                                            | PimCommon::SimpleStringListEditor::Modify);
    mWhiteListEditor = new ConfirmAddressSimpleStringListEditor(groupBoxWhiteList,
                                                                buttonCode,
                                                                i18n("A&dd..."),
                                                                i18n("Re&move"),
                                                                i18n("Mod&ify..."),
                                                                i18n("Enter new email address:"));
    mWhiteListEditor->setObjectName(QStringLiteral("whitelisteditor"));
    mWhiteListEditor->setRemoveDialogLabel(i18n("Do you want to remove this email address?"));
    layoutWhiteList->addWidget(mWhiteListEditor);
    connect(mWhiteListEditor, &ConfirmAddressSimpleStringListEditor::changed, this, &ConfirmAddressConfigureTabWidget::configureChanged);
}

ConfirmAddressConfigureTabWidget::~ConfirmAddressConfigureTabWidget() = default;

void ConfirmAddressConfigureTabWidget::resetSettings()
{
    mDomainNameListEditor->setStringList({});
    mWhiteListEditor->setStringList({});
}

void ConfirmAddressConfigureTabWidget::loadSettings(const KConfigGroup &grp)
{
    KConfigGroup identityGroup = grp.group(QStringLiteral("Confirm Address %1").arg(mIdentity));
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
    KConfigGroup identityGroup = grp.group(QStringLiteral("Confirm Address %1").arg(mIdentity));
    identityGroup.writeEntry("Domains", mDomainNameListEditor->stringList());
    identityGroup.writeEntry("Emails", mWhiteListEditor->stringList());
    identityGroup.writeEntry("RejectDomain", mRejectedDomain->isChecked());
}

void ConfirmAddressConfigureTabWidget::setIdentity(uint identity)
{
    mIdentity = identity;
}

#include "moc_confirmaddressconfiguretabwidget.cpp"
