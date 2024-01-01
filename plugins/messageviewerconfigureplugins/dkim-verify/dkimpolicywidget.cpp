/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

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
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mVerifyIfEmailMustBeSigned->setObjectName(QLatin1StringView("kcfg_CheckIfEmailShouldBeSigned"));
    mainLayout->addWidget(mVerifyIfEmailMustBeSigned);
    connect(mVerifyIfEmailMustBeSigned, &QCheckBox::toggled, this, [this](bool state) {
        mUseDMARC->setEnabled(state);
        mUseDefaultRules->setEnabled(state);
        mRulesButton->setEnabled(state);
        mAutoGenerateOnlyIfSenderInSDID->setEnabled(state);
        mAutoGenerateRule->setEnabled(state);
        mReadAuthResultHeader->setEnabled(state);
    });

    mUseDMARC->setObjectName(QLatin1StringView("kcfg_UseDMarc"));
    mUseDMARC->setEnabled(false);
    mainLayout->addWidget(mUseDMARC);

    mReadAuthResultHeader->setObjectName(QLatin1StringView("kcfg_UseAuthenticationResults"));
    mReadAuthResultHeader->setEnabled(false);
    mainLayout->addWidget(mReadAuthResultHeader);

    mUseDefaultRules->setObjectName(QLatin1StringView("kcfg_UseDefaultRules"));
    mUseDefaultRules->setEnabled(false);
    mainLayout->addWidget(mUseDefaultRules);

    mAutoGenerateRule->setObjectName(QLatin1StringView("kcfg_AutogenerateRule"));
    mAutoGenerateRule->setEnabled(false);
    mainLayout->addWidget(mAutoGenerateRule);

    auto autogenerateOnlyLayout = new QHBoxLayout;
    autogenerateOnlyLayout->setContentsMargins({});
    mainLayout->addLayout(autogenerateOnlyLayout);

    auto item = new QSpacerItem(30, 0);
    autogenerateOnlyLayout->addItem(item);

    mAutoGenerateOnlyIfSenderInSDID->setObjectName(QLatin1StringView("kcfg_AutogenerateRuleOnlyIfSenderOnSDID"));
    mAutoGenerateOnlyIfSenderInSDID->setEnabled(false);
    autogenerateOnlyLayout->addWidget(mAutoGenerateOnlyIfSenderInSDID);

    auto ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
    mRulesButton->setObjectName(QLatin1StringView("rules"));
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
