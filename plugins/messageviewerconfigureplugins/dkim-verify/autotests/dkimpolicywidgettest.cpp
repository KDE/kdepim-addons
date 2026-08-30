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
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(DKIMPolicyWidgetTest)
DKIMPolicyWidgetTest::DKIMPolicyWidgetTest(QObject *parent)
    : QObject(parent)
{
}

DKIMPolicyWidgetTest::~DKIMPolicyWidgetTest() = default;

void DKIMPolicyWidgetTest::shouldHaveDefaultValues()
{
    DKIMPolicyWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    const auto mVerifyIfEmailMustBeSigned = w.findChild<QCheckBox *>(u"kcfg_CheckIfEmailShouldBeSigned"_s);
    QVERIFY(mVerifyIfEmailMustBeSigned);
    QVERIFY(!mVerifyIfEmailMustBeSigned->text().isEmpty());
    QVERIFY(mVerifyIfEmailMustBeSigned->isEnabled());

    const auto mUseDMARC = w.findChild<QCheckBox *>(u"kcfg_UseDMarc"_s);
    QVERIFY(mUseDMARC);
    QVERIFY(!mUseDMARC->text().isEmpty());
    QVERIFY(!mUseDMARC->isEnabled());

    const auto mUseDefaultRules = w.findChild<QCheckBox *>(u"kcfg_UseDefaultRules"_s);
    QVERIFY(mUseDefaultRules);
    QVERIFY(!mUseDefaultRules->text().isEmpty());
    QVERIFY(!mUseDefaultRules->isEnabled());

    const auto mRulesButton = w.findChild<QPushButton *>(u"rules"_s);
    QVERIFY(mRulesButton);
    QVERIFY(!mRulesButton->isEnabled());
    QVERIFY(!mRulesButton->text().isEmpty());

    const auto mAutoGenerateRule = w.findChild<QCheckBox *>(u"kcfg_AutogenerateRule"_s);
    QVERIFY(mAutoGenerateRule);
    QVERIFY(!mAutoGenerateRule->text().isEmpty());
    QVERIFY(!mAutoGenerateRule->isEnabled());

    const auto mReadAuthResultHeader = w.findChild<QCheckBox *>(u"kcfg_UseAuthenticationResults"_s);
    QVERIFY(mReadAuthResultHeader);
    QVERIFY(!mReadAuthResultHeader->text().isEmpty());
    QVERIFY(!mReadAuthResultHeader->isEnabled());

    const auto mAutoGenerateOnlyIfSenderInSDID = w.findChild<QCheckBox *>(u"kcfg_AutogenerateRuleOnlyIfSenderOnSDID"_s);
    QVERIFY(mAutoGenerateOnlyIfSenderInSDID);
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->text().isEmpty());
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->isEnabled());
}

#include "moc_dkimpolicywidgettest.cpp"
