/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidgettest.h"
#include "dkimgeneralwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMGeneralWidgetTest)
DKIMGeneralWidgetTest::DKIMGeneralWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMGeneralWidgetTest::shouldHaveDefaultValues()
{
    DKIMGeneralWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    const auto mEnableDkimSupport = w.findChild<QCheckBox *>(QStringLiteral("kcfg_EnabledDkim"));
    QVERIFY(mEnableDkimSupport);
    QVERIFY(!mEnableDkimSupport->text().isEmpty());
    QVERIFY(!mEnableDkimSupport->isChecked());

    const auto mSaveResult = w.findChild<QCheckBox *>(QStringLiteral("kcfg_SaveDkimResult"));
    QVERIFY(mSaveResult);
    QVERIFY(!mSaveResult->text().isEmpty());
    QVERIFY(!mSaveResult->isChecked());

    const auto mSaveKey = w.findChild<QComboBox *>(QStringLiteral("kcfg_SaveKey"));
    QVERIFY(mSaveKey);

    const auto mUseOnlyAuthenticationResult = w.findChild<QCheckBox *>(QStringLiteral("kcfg_UseOnlyAuthenticationResults"));
    QVERIFY(mUseOnlyAuthenticationResult);
    QVERIFY(!mUseOnlyAuthenticationResult->text().isEmpty());
    QVERIFY(!mUseOnlyAuthenticationResult->isChecked());
}

#include "moc_dkimgeneralwidgettest.cpp"
