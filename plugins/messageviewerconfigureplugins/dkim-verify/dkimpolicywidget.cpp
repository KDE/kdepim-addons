/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimpolicywidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManageRulesDialog>
#include <MessageViewer/MessageViewerSettings>
#include <QCheckBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

DKIMPolicyWidget::DKIMPolicyWidget(QWidget *parent)
    : QWidget(parent)
    , mVerifyIfEmailMustBeSigned(new QCheckBox(i18n("Check if e-mail should be signed"), this))
    , mUseDMARC(new QCheckBox(i18n("Use DMARC to heuristically determine if an e-mail should be signed"), this))
    , mUseDefaultRules(new QCheckBox(i18n("Use default rule"), this))
    , mAutoGenerateRule(new QCheckBox(i18n("Autogenerate rule"), this))
    , mReadAuthResultHeader(new QCheckBox(i18n("Read Authentication-Results header"), this))
    , mAutoGenerateOnlyIfSenderInSDID(new QCheckBox(i18n("Autogenerate when Sender in SDID"), this))
    , mRulesButton(new QPushButton(i18n("Show Rules"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mVerifyIfEmailMustBeSigned->setObjectName(QStringLiteral("kcfg_CheckIfEmailShouldBeSigned"));
    mainLayout->addWidget(mVerifyIfEmailMustBeSigned);
    connect(mVerifyIfEmailMustBeSigned, &QCheckBox::toggled, this, [this](bool state) {
        mUseDMARC->setEnabled(state);
        mUseDefaultRules->setEnabled(state);
        mRulesButton->setEnabled(state);
        mAutoGenerateOnlyIfSenderInSDID->setEnabled(state);
        mAutoGenerateRule->setEnabled(state);
        mReadAuthResultHeader->setEnabled(state);
    });

    mUseDMARC->setObjectName(QStringLiteral("kcfg_UseDMarc"));
    mUseDMARC->setEnabled(false);
    mainLayout->addWidget(mUseDMARC);

    mReadAuthResultHeader->setObjectName(QStringLiteral("kcfg_UseAuthenticationResults"));
    mReadAuthResultHeader->setEnabled(false);
    mainLayout->addWidget(mReadAuthResultHeader);

    mUseDefaultRules->setObjectName(QStringLiteral("kcfg_UseDefaultRules"));
    mUseDefaultRules->setEnabled(false);
    mainLayout->addWidget(mUseDefaultRules);

    mAutoGenerateRule->setObjectName(QStringLiteral("kcfg_AutogenerateRule"));
    mAutoGenerateRule->setEnabled(false);
    mainLayout->addWidget(mAutoGenerateRule);

    auto autogenerateOnlyLayout = new QHBoxLayout;
    autogenerateOnlyLayout->setContentsMargins({});
    mainLayout->addLayout(autogenerateOnlyLayout);

    auto item = new QSpacerItem(30, 0);
    autogenerateOnlyLayout->addItem(item);

    mAutoGenerateOnlyIfSenderInSDID->setObjectName(QStringLiteral("kcfg_AutogenerateRuleOnlyIfSenderOnSDID"));
    mAutoGenerateOnlyIfSenderInSDID->setEnabled(false);
    autogenerateOnlyLayout->addWidget(mAutoGenerateOnlyIfSenderInSDID);

    auto ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
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

DKIMPolicyWidget::~DKIMPolicyWidget() = default;
