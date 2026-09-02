/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimpolicywidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManageRulesDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

DKIMPolicyWidget::DKIMPolicyWidget(QWidget *parent)
    : QWidget(parent)
    , mVerifyIfEmailMustBeSigned(new QCheckBox(i18nc("@option:check", "Check if e-mail should be signed"), this))
    , mUseDMARC(new QCheckBox(i18nc("@option:check", "Use DMARC to heuristically determine if an e-mail should be signed"), this))
    , mUseDefaultRules(new QCheckBox(i18nc("@option:check", "Use default rule"), this))
    , mAutoGenerateRule(new QCheckBox(i18nc("@option:check", "Autogenerate rule"), this))
    , mReadAuthResultHeader(new QCheckBox(i18nc("@option:check", "Read Authentication-Results header"), this))
    , mAutoGenerateOnlyIfSenderInSDID(new QCheckBox(i18nc("@option:check", "Autogenerate when Sender in SDID"), this))
    , mRulesButton(new QPushButton(i18nc("@action:button", "Show Rules"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mVerifyIfEmailMustBeSigned->setObjectName("kcfg_CheckIfEmailShouldBeSigned"_L1);
    mainLayout->addWidget(mVerifyIfEmailMustBeSigned);
    connect(mVerifyIfEmailMustBeSigned, &QCheckBox::toggled, this, [this](bool state) {
        mUseDMARC->setEnabled(state);
        mUseDefaultRules->setEnabled(state);
        mRulesButton->setEnabled(state);
        mAutoGenerateOnlyIfSenderInSDID->setEnabled(state);
        mAutoGenerateRule->setEnabled(state);
        mReadAuthResultHeader->setEnabled(state);
    });

    mUseDMARC->setObjectName("kcfg_UseDMarc"_L1);
    mUseDMARC->setEnabled(false);
    mainLayout->addWidget(mUseDMARC);

    mReadAuthResultHeader->setObjectName("kcfg_UseAuthenticationResults"_L1);
    mReadAuthResultHeader->setEnabled(false);
    mainLayout->addWidget(mReadAuthResultHeader);

    mUseDefaultRules->setObjectName("kcfg_UseDefaultRules"_L1);
    mUseDefaultRules->setEnabled(false);
    mainLayout->addWidget(mUseDefaultRules);

    mAutoGenerateRule->setObjectName("kcfg_AutogenerateRule"_L1);
    mAutoGenerateRule->setEnabled(false);
    mainLayout->addWidget(mAutoGenerateRule);

    auto autogenerateOnlyLayout = new QHBoxLayout;
    autogenerateOnlyLayout->setContentsMargins({});
    mainLayout->addLayout(autogenerateOnlyLayout);

    auto item = new QSpacerItem(30, 0);
    autogenerateOnlyLayout->addItem(item);

    mAutoGenerateOnlyIfSenderInSDID->setObjectName("kcfg_AutogenerateRuleOnlyIfSenderOnSDID"_L1);
    mAutoGenerateOnlyIfSenderInSDID->setEnabled(false);
    autogenerateOnlyLayout->addWidget(mAutoGenerateOnlyIfSenderInSDID);

    auto ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
    mRulesButton->setObjectName("rules"_L1);
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

#include "moc_dkimpolicywidget.cpp"
