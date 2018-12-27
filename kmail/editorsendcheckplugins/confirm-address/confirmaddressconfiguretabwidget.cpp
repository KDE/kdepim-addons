/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "confirmaddressconfiguretabwidget.h"
#include "confirmaddresssimplestringlisteditor.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>

ConfirmAddressConfigureTabWidget::ConfirmAddressConfigureTabWidget(QWidget *parent)
    : QWidget(parent)
    , mIdentity(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    QGroupBox *groupBoxDomainName = new QGroupBox(this);
    groupBoxDomainName->setObjectName(QStringLiteral("groupboxdomainname"));
    mainLayout->addWidget(groupBoxDomainName);
    QVBoxLayout *layoutDomainName = new QVBoxLayout(groupBoxDomainName);
    layoutDomainName->setObjectName(QStringLiteral("layoutdomainname"));

    QHBoxLayout *radioButtonLayout = new QHBoxLayout;
    layoutDomainName->addLayout(radioButtonLayout);
    radioButtonLayout->setAlignment(Qt::AlignHCenter);

    mAcceptedDomain = new QRadioButton(i18n("Accepted Domain Name"), this);
    mAcceptedDomain->setObjectName(QStringLiteral("acceptdomainname"));
    radioButtonLayout->addWidget(mAcceptedDomain);
    mAcceptedDomain->setChecked(true);

    mRejectedDomain = new QRadioButton(i18n("Rejected Domain Name"), this);
    mRejectedDomain->setObjectName(QStringLiteral("rejectdomainname"));
    radioButtonLayout->addWidget(mRejectedDomain);

    PimCommon::SimpleStringListEditor::ButtonCode buttonCode
        = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mDomainNameListEditor
        = new ConfirmAddressSimpleStringListEditor(groupBoxDomainName, buttonCode,
                                                   i18n("A&dd..."), i18n("Re&move"),
                                                   i18n("Mod&ify..."),
                                                   i18n("Enter new domain name:"));
    mDomainNameListEditor->setObjectName(QStringLiteral("domainnamelisteditor"));
    connect(mDomainNameListEditor, &ConfirmAddressSimpleStringListEditor::changed,
            this, &ConfirmAddressConfigureTabWidget::configureChanged);
    layoutDomainName->addWidget(mDomainNameListEditor);

    QGroupBox *groupBoxWhiteList = new QGroupBox(i18n("Whitelist of Addresses"), this);
    groupBoxWhiteList->setObjectName(QStringLiteral("groupboxwhitelist"));
    mainLayout->addWidget(groupBoxWhiteList);
    QVBoxLayout *layoutWhiteList = new QVBoxLayout(groupBoxWhiteList);
    layoutWhiteList->setObjectName(QStringLiteral("layoutwhitelist"));

    buttonCode
        = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mWhiteListEditor
        = new ConfirmAddressSimpleStringListEditor(groupBoxWhiteList, buttonCode,
                                                   i18n("A&dd..."), i18n("Re&move"),
                                                   i18n("Mod&ify..."),
                                                   i18n("Enter new email address:"));
    mWhiteListEditor->setObjectName(QStringLiteral("whitelisteditor"));
    layoutWhiteList->addWidget(mWhiteListEditor);
    connect(mWhiteListEditor, &ConfirmAddressSimpleStringListEditor::changed,
            this, &ConfirmAddressConfigureTabWidget::configureChanged);
}

ConfirmAddressConfigureTabWidget::~ConfirmAddressConfigureTabWidget()
{
}

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
