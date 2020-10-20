/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

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
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    QCheckBox *mEnableDkimSupport = w.findChild<QCheckBox *>(QStringLiteral("enableDkimSupport"));
    QVERIFY(mEnableDkimSupport);
    QVERIFY(!mEnableDkimSupport->text().isEmpty());
    QVERIFY(!mEnableDkimSupport->isChecked());

    QCheckBox *mSaveResult = w.findChild<QCheckBox *>(QStringLiteral("mSaveResult"));
    QVERIFY(mSaveResult);
    QVERIFY(!mSaveResult->text().isEmpty());
    QVERIFY(!mSaveResult->isChecked());

    QComboBox *mSaveKey = w.findChild<QComboBox *>(QStringLiteral("mSaveKey"));
    QVERIFY(mSaveKey);

    QCheckBox *mUseOnlyAuthenticationResult = w.findChild<QCheckBox *>(QStringLiteral("mUseOnlyAuthenticationResult"));
    QVERIFY(mUseOnlyAuthenticationResult);
    QVERIFY(!mUseOnlyAuthenticationResult->text().isEmpty());
    QVERIFY(!mUseOnlyAuthenticationResult->isChecked());
}
