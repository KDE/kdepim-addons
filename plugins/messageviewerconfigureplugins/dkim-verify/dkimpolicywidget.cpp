/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimpolicywidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>
#include <MessageViewer/DKIMManageRulesDialog>
#include <MessageViewer/MessageViewerSettings>
#include <PimCommon/ConfigureImmutableWidgetUtils>
#include <QPointer>
#include <QPushButton>
#include <QSpacerItem>

using namespace PimCommon::ConfigureImmutableWidgetUtils;

DKIMPolicyWidget::DKIMPolicyWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mVerifyIfEmailMustBeSigned = new QCheckBox(i18n("Check if e-mail should be signed"), this);
    mVerifyIfEmailMustBeSigned->setObjectName(QStringLiteral("mVerifyIfEmailMustBeSigned"));
    mainLayout->addWidget(mVerifyIfEmailMustBeSigned);
    connect(mVerifyIfEmailMustBeSigned, &QCheckBox::toggled, this, [this](bool state) {
        mUseDMARC->setEnabled(state);
        mUseDefaultRules->setEnabled(state);
        mRulesButton->setEnabled(state);
        mAutoGenerateOnlyIfSenderInSDID->setEnabled(state);
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
    mainLayout->addWidget(mReadAuthResultHeader);

    mUseDefaultRules = new QCheckBox(i18n("Use default rule"), this);
    mUseDefaultRules->setObjectName(QStringLiteral("mUseDefaultRules"));
    mUseDefaultRules->setEnabled(false);
    mainLayout->addWidget(mUseDefaultRules);

    mAutoGenerateRule = new QCheckBox(i18n("Autogenerate rule"), this);
    mAutoGenerateRule->setObjectName(QStringLiteral("mAutoGenerateRule"));
    mAutoGenerateRule->setEnabled(false);
    mainLayout->addWidget(mAutoGenerateRule);

    QHBoxLayout *autogenerateOnlyLayout = new QHBoxLayout;
    autogenerateOnlyLayout->setContentsMargins({});
    mainLayout->addLayout(autogenerateOnlyLayout);

    QSpacerItem *item = new QSpacerItem(30, 0);
    autogenerateOnlyLayout->addItem(item);

    mAutoGenerateOnlyIfSenderInSDID = new QCheckBox(i18n("Autogenerate when Sender in SDID"), this);
    mAutoGenerateOnlyIfSenderInSDID->setObjectName(QStringLiteral("mAutoGenerateOnlyIfSenderInSDID"));
    mAutoGenerateOnlyIfSenderInSDID->setEnabled(false);
    autogenerateOnlyLayout->addWidget(mAutoGenerateOnlyIfSenderInSDID);

    QHBoxLayout *ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
    mRulesButton = new QPushButton(i18n("Show Rules"), this);
    mRulesButton->setObjectName(QStringLiteral("rules"));
    mRulesButton->setEnabled(false);
    ruleLayout->addWidget(mRulesButton);
    connect(mRulesButton, &QPushButton::clicked, this, [this]() {
        MessageViewer::DKIMManageRulesDialog dlg(this);
        dlg.exec();
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
    loadWidget(mAutoGenerateOnlyIfSenderInSDID, MessageViewer::MessageViewerSettings::self()->autogenerateRuleOnlyIfSenderOnSDIDItem());
}

void DKIMPolicyWidget::saveSettings()
{
    saveCheckBox(mVerifyIfEmailMustBeSigned, MessageViewer::MessageViewerSettings::self()->checkIfEmailShouldBeSignedItem());
    saveCheckBox(mUseDMARC, MessageViewer::MessageViewerSettings::self()->useDMarcItem());
    saveCheckBox(mUseDefaultRules, MessageViewer::MessageViewerSettings::self()->useDefaultRulesItem());
    saveCheckBox(mAutoGenerateRule, MessageViewer::MessageViewerSettings::self()->autogenerateRuleItem());
    saveCheckBox(mReadAuthResultHeader, MessageViewer::MessageViewerSettings::self()->useAuthenticationResultsItem());
    saveCheckBox(mAutoGenerateOnlyIfSenderInSDID, MessageViewer::MessageViewerSettings::self()->autogenerateRuleOnlyIfSenderOnSDIDItem());
}

void DKIMPolicyWidget::resetSettings()
{
    const bool bUseDefaults = MessageViewer::MessageViewerSettings::self()->useDefaults(true);
    loadSettings();
    MessageViewer::MessageViewerSettings::self()->useDefaults(bUseDefaults);
}
