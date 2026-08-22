/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimpolicywidgettest.h"
#include "dkimpolicywidget.h"
#include <QCheckBox>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMPolicyWidgetTest)
DKIMPolicyWidgetTest::DKIMPolicyWidgetTest(QObject *parent)
    : QObject(parent)
{
}

DKIMPolicyWidgetTest::~DKIMPolicyWidgetTest() = default;

void DKIMPolicyWidgetTest::shouldHaveDefaultValues()
{
    DKIMPolicyWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    const auto mVerifyIfEmailMustBeSigned = w.findChild<QCheckBox *>(QStringLiteral("kcfg_CheckIfEmailShouldBeSigned"));
    QVERIFY(mVerifyIfEmailMustBeSigned);
    QVERIFY(!mVerifyIfEmailMustBeSigned->text().isEmpty());
    QVERIFY(mVerifyIfEmailMustBeSigned->isEnabled());

    const auto mUseDMARC = w.findChild<QCheckBox *>(QStringLiteral("kcfg_UseDMarc"));
    QVERIFY(mUseDMARC);
    QVERIFY(!mUseDMARC->text().isEmpty());
    QVERIFY(!mUseDMARC->isEnabled());

    const auto mUseDefaultRules = w.findChild<QCheckBox *>(QStringLiteral("kcfg_UseDefaultRules"));
    QVERIFY(mUseDefaultRules);
    QVERIFY(!mUseDefaultRules->text().isEmpty());
    QVERIFY(!mUseDefaultRules->isEnabled());

    const auto mRulesButton = w.findChild<QPushButton *>(QStringLiteral("rules"));
    QVERIFY(mRulesButton);
    QVERIFY(!mRulesButton->isEnabled());
    QVERIFY(!mRulesButton->text().isEmpty());

    const auto mAutoGenerateRule = w.findChild<QCheckBox *>(QStringLiteral("kcfg_AutogenerateRule"));
    QVERIFY(mAutoGenerateRule);
    QVERIFY(!mAutoGenerateRule->text().isEmpty());
    QVERIFY(!mAutoGenerateRule->isEnabled());

    const auto mReadAuthResultHeader = w.findChild<QCheckBox *>(QStringLiteral("kcfg_UseAuthenticationResults"));
    QVERIFY(mReadAuthResultHeader);
    QVERIFY(!mReadAuthResultHeader->text().isEmpty());
    QVERIFY(!mReadAuthResultHeader->isEnabled());

    const auto mAutoGenerateOnlyIfSenderInSDID = w.findChild<QCheckBox *>(QStringLiteral("kcfg_AutogenerateRuleOnlyIfSenderOnSDID"));
    QVERIFY(mAutoGenerateOnlyIfSenderInSDID);
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->text().isEmpty());
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->isEnabled());
}

#include "moc_dkimpolicywidgettest.cpp"
