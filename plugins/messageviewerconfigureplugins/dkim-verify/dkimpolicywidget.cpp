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
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    auto verifyIfEmailMustBeSigned = new QCheckBox(i18nc("@option:check", "Check if e-mail should be signed"), this);
    verifyIfEmailMustBeSigned->setObjectName("kcfg_CheckIfEmailShouldBeSigned"_L1);
    mainLayout->addWidget(verifyIfEmailMustBeSigned);

    auto useDMARC = new QCheckBox(i18nc("@option:check", "Use DMARC to heuristically determine if an e-mail should be signed"), this);
    useDMARC->setObjectName("kcfg_UseDMarc"_L1);
    useDMARC->setEnabled(false);
    mainLayout->addWidget(useDMARC);

    auto readAuthResultHeader = new QCheckBox(i18nc("@option:check", "Read Authentication-Results header"), this);
    readAuthResultHeader->setObjectName("kcfg_UseAuthenticationResults"_L1);
    readAuthResultHeader->setEnabled(false);
    mainLayout->addWidget(readAuthResultHeader);

    auto useDefaultRules = new QCheckBox(i18nc("@option:check", "Use default rule"), this);
    useDefaultRules->setObjectName("kcfg_UseDefaultRules"_L1);
    useDefaultRules->setEnabled(false);
    mainLayout->addWidget(useDefaultRules);

    auto autoGenerateRule = new QCheckBox(i18nc("@option:check", "Autogenerate rule"), this);
    autoGenerateRule->setObjectName("kcfg_AutogenerateRule"_L1);
    autoGenerateRule->setEnabled(false);
    mainLayout->addWidget(autoGenerateRule);

    auto autogenerateOnlyLayout = new QHBoxLayout;
    autogenerateOnlyLayout->setContentsMargins({});
    mainLayout->addLayout(autogenerateOnlyLayout);

    auto item = new QSpacerItem(30, 0);
    autogenerateOnlyLayout->addItem(item);

    auto autoGenerateOnlyIfSenderInSDID = new QCheckBox(i18nc("@option:check", "Autogenerate when Sender in SDID"), this);
    autoGenerateOnlyIfSenderInSDID->setObjectName("kcfg_AutogenerateRuleOnlyIfSenderOnSDID"_L1);
    autoGenerateOnlyIfSenderInSDID->setEnabled(false);
    autogenerateOnlyLayout->addWidget(autoGenerateOnlyIfSenderInSDID);

    auto ruleLayout = new QHBoxLayout;
    mainLayout->addLayout(ruleLayout);
    auto rulesButton = new QPushButton(i18nc("@action:button", "Show Rules"), this);
    rulesButton->setObjectName("rules"_L1);
    rulesButton->setEnabled(false);
    ruleLayout->addWidget(rulesButton);
    connect(rulesButton, &QPushButton::clicked, this, [this]() {
        MessageViewer::DKIMManageRulesDialog dlg(this);
        dlg.exec();
    });
    ruleLayout->addStretch(1);

    connect(verifyIfEmailMustBeSigned,
            &QCheckBox::toggled,
            this,
            [useDMARC, useDefaultRules, rulesButton, autoGenerateOnlyIfSenderInSDID, autoGenerateRule, readAuthResultHeader](bool state) {
                useDMARC->setEnabled(state);
                useDefaultRules->setEnabled(state);
                rulesButton->setEnabled(state);
                autoGenerateOnlyIfSenderInSDID->setEnabled(state);
                autoGenerateRule->setEnabled(state);
                readAuthResultHeader->setEnabled(state);
            });

    mainLayout->addStretch(1);
}

DKIMPolicyWidget::~DKIMPolicyWidget() = default;

#include "moc_dkimpolicywidget.cpp"
