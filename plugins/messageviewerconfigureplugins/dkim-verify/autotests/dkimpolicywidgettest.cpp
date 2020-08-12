/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

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

DKIMPolicyWidgetTest::~DKIMPolicyWidgetTest()
{
}

void DKIMPolicyWidgetTest::shouldHaveDefaultValues()
{
    DKIMPolicyWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mVerifyIfEmailMustBeSigned = w.findChild<QCheckBox *>(QStringLiteral("mVerifyIfEmailMustBeSigned"));
    QVERIFY(mVerifyIfEmailMustBeSigned);
    QVERIFY(!mVerifyIfEmailMustBeSigned->text().isEmpty());
    QVERIFY(mVerifyIfEmailMustBeSigned->isEnabled());

    QCheckBox *mUseDMARC = w.findChild<QCheckBox *>(QStringLiteral("mUseDMARC"));
    QVERIFY(mUseDMARC);
    QVERIFY(!mUseDMARC->text().isEmpty());
    QVERIFY(!mUseDMARC->isEnabled());

    QCheckBox *mUseDefaultRules = w.findChild<QCheckBox *>(QStringLiteral("mUseDefaultRules"));
    QVERIFY(mUseDefaultRules);
    QVERIFY(!mUseDefaultRules->text().isEmpty());
    QVERIFY(!mUseDefaultRules->isEnabled());

    QPushButton *mRulesButton = w.findChild<QPushButton *>(QStringLiteral("rules"));
    QVERIFY(mRulesButton);
    QVERIFY(!mRulesButton->isEnabled());
    QVERIFY(!mRulesButton->text().isEmpty());

    QCheckBox *mAutoGenerateRule = w.findChild<QCheckBox *>(QStringLiteral("mAutoGenerateRule"));
    QVERIFY(mAutoGenerateRule);
    QVERIFY(!mAutoGenerateRule->text().isEmpty());
    QVERIFY(!mAutoGenerateRule->isEnabled());

    QCheckBox *mReadAuthResultHeader = w.findChild<QCheckBox *>(QStringLiteral("mReadAuthResultHeader"));
    QVERIFY(mReadAuthResultHeader);
    QVERIFY(!mReadAuthResultHeader->text().isEmpty());
    QVERIFY(!mReadAuthResultHeader->isEnabled());

    QCheckBox *mAutoGenerateOnlyIfSenderInSDID = w.findChild<QCheckBox *>(QStringLiteral("mAutoGenerateOnlyIfSenderInSDID"));
    QVERIFY(mAutoGenerateOnlyIfSenderInSDID);
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->text().isEmpty());
    QVERIFY(!mAutoGenerateOnlyIfSenderInSDID->isEnabled());
}
