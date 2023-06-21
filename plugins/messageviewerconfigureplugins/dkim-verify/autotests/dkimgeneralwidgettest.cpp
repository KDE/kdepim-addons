/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidgettest.h"
#include "dkimgeneralwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMGeneralWidgetTest)
DKIMGeneralWidgetTest::DKIMGeneralWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMGeneralWidgetTest::shouldHaveDefaultValues()
{
    DKIMGeneralWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mEnableDkimSupport = w.findChild<QCheckBox *>(QStringLiteral("kcfg_EnabledDkim"));
    QVERIFY(mEnableDkimSupport);
    QVERIFY(!mEnableDkimSupport->text().isEmpty());
    QVERIFY(!mEnableDkimSupport->isChecked());

    auto mSaveResult = w.findChild<QCheckBox *>(QStringLiteral("kcfg_SaveDkimResult"));
    QVERIFY(mSaveResult);
    QVERIFY(!mSaveResult->text().isEmpty());
    QVERIFY(!mSaveResult->isChecked());

    auto mSaveKey = w.findChild<QComboBox *>(QStringLiteral("kcfg_SaveKey"));
    QVERIFY(mSaveKey);

    auto mUseOnlyAuthenticationResult = w.findChild<QCheckBox *>(QStringLiteral("kcfg_UseOnlyAuthenticationResults"));
    QVERIFY(mUseOnlyAuthenticationResult);
    QVERIFY(!mUseOnlyAuthenticationResult->text().isEmpty());
    QVERIFY(!mUseOnlyAuthenticationResult->isChecked());
}

#include "moc_dkimgeneralwidgettest.cpp"
