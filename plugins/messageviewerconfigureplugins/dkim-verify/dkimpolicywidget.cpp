/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimpolicywidget.h"
#include "dkimmanagerulesdialog.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>

#include "messageviewer/messageviewersettings.h"
#include <PimCommon/ConfigureImmutableWidgetUtils>
#include <QPointer>
#include <QPushButton>

using namespace PimCommon::ConfigureImmutableWidgetUtils;

DKIMPolicyWidget::DKIMPolicyWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mVerifyIfEmailMustBeSigned = new QCheckBox(i18n("Check if e-mail should be signed"), this);
    mVerifyIfEmailMustBeSigned->setObjectName(QStringLiteral("mVerifyIfEmailMustBeSigned"));
    mainLayout->addWidget(mVerifyIfEmailMustBeSigned);
    connect(mVerifyIfEmailMustBeSigned, &QCheckBox::toggled, this, [this](bool state) {
        mUseDMARC->setEnabled(state);
        mUseDefaultRules->setEnabled(state);
        mRulesButton->setEnabled(state);
        mAutoGenerateRule->setEnabled(state);
        mReadAuthResultHeader->setEnabled(state);
    });

    mUseDMARC = new QCheckBox(i18n("Use DMARC to heuristically determine if an e-mail should be signed"), this);
    mUseDMARC->setObjectName(QStringLiteral("mUseDMARC"));
    mUseDMARC->setEnabled(false);
    mainLayout->addWidget(mUseDMARC);

    mReadAuthResultHeader = new QCheckBox(i18n("Read Authentication-Results header"), this);
    mReadAuthResultHeader->setObjectName(QStringLiteral("mReadAuthResultHeader"));
    mReadAuthResultHeader->setEnabled(false);
    //mReadAuthResultHeader->setVisible(false); //Reenable when code will be clean!
    mainLayout->addWidget(mReadAuthResultHeader);

    mUseDefaultRules = new QCheckBox(i18n("Use default rule"), this);
    mUseDefaultRules->setObjectName(QStringLiteral("mUseDefaultRules"));
    mUseDefaultRules->setEnabled(false);
    mainLayout->addWidget(mUseDefaultRules);

    mAutoGenerateRule = new QCheckBox(i18n("Autogenerate rule"), this);
    mAutoGenerateRule->setObjectName(QStringLiteral("mAutoGenerateRule"));
    mAutoGenerateRule->setEnabled(false);
    mainLayout->addWidget(mAutoGenerateRule);

    QHBoxLayout *ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
    mRulesButton = new QPushButton(i18n("Show Rules"), this);
    mRulesButton->setObjectName(QStringLiteral("rules"));
    mRulesButton->setEnabled(false);
    ruleLayout->addWidget(mRulesButton);
    connect(mRulesButton, &QPushButton::clicked, this, [this]() {
        QPointer<DKIMManageRulesDialog> dlg = new DKIMManageRulesDialog(this);
        dlg->exec();
        delete dlg;
    });
    ruleLayout->addStretch(1);

    mainLayout->addStretch(1);
}

DKIMPolicyWidget::~DKIMPolicyWidget()
{
}

void DKIMPolicyWidget::loadSettings()
{
    loadWidget(mVerifyIfEmailMustBeSigned, MessageViewer::MessageViewerSettings::self()->checkIfEmailShouldBeSignedItem());
    loadWidget(mUseDMARC, MessageViewer::MessageViewerSettings::self()->useDMarcItem());
    loadWidget(mUseDefaultRules, MessageViewer::MessageViewerSettings::self()->useDefaultRulesItem());
    loadWidget(mAutoGenerateRule, MessageViewer::MessageViewerSettings::self()->autogenerateRuleItem());
    loadWidget(mReadAuthResultHeader, MessageViewer::MessageViewerSettings::self()->useAuthenticationResultsItem());
}

void DKIMPolicyWidget::saveSettings()
{
    saveCheckBox(mVerifyIfEmailMustBeSigned, MessageViewer::MessageViewerSettings::self()->checkIfEmailShouldBeSignedItem());
    saveCheckBox(mUseDMARC, MessageViewer::MessageViewerSettings::self()->useDMarcItem());
    saveCheckBox(mUseDefaultRules, MessageViewer::MessageViewerSettings::self()->useDefaultRulesItem());
    saveCheckBox(mAutoGenerateRule, MessageViewer::MessageViewerSettings::self()->autogenerateRuleItem());
    saveCheckBox(mReadAuthResultHeader, MessageViewer::MessageViewerSettings::self()->useAuthenticationResultsItem());
}

void DKIMPolicyWidget::resetSettings()
{
    const bool bUseDefaults = MessageViewer::MessageViewerSettings::self()->useDefaults(true);
    loadSettings();
    MessageViewer::MessageViewerSettings::self()->useDefaults(bUseDefaults);
}
