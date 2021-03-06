/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

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

    auto mEnableDkimSupport = w.findChild<QCheckBox *>(QStringLiteral("enableDkimSupport"));
    QVERIFY(mEnableDkimSupport);
    QVERIFY(!mEnableDkimSupport->text().isEmpty());
    QVERIFY(!mEnableDkimSupport->isChecked());

    auto mSaveResult = w.findChild<QCheckBox *>(QStringLiteral("mSaveResult"));
    QVERIFY(mSaveResult);
    QVERIFY(!mSaveResult->text().isEmpty());
    QVERIFY(!mSaveResult->isChecked());

    auto mSaveKey = w.findChild<QComboBox *>(QStringLiteral("mSaveKey"));
    QVERIFY(mSaveKey);

    auto mUseOnlyAuthenticationResult = w.findChild<QCheckBox *>(QStringLiteral("mUseOnlyAuthenticationResult"));
    QVERIFY(mUseOnlyAuthenticationResult);
    QVERIFY(!mUseOnlyAuthenticationResult->text().isEmpty());
    QVERIFY(!mUseOnlyAuthenticationResult->isChecked());
}
