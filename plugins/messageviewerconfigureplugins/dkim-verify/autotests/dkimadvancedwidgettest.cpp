/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidgettest.h"
#include "dkimadvancedwidget.h"
#include <QTest>
#include <QFormLayout>
#include <QCheckBox>
#include <QComboBox>
QTEST_MAIN(DKIMAdvancedWidgetTest)

DKIMAdvancedWidgetTest::DKIMAdvancedWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMAdvancedWidgetTest::shouldHaveDefaultValues()
{
    DKIMAdvancedWidget w;
    QFormLayout *mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mCheckDKIMWhenOnlyTesting = w.findChild<QCheckBox *>(QStringLiteral("mCheckDKIMWhenOnlyTesting"));
    QVERIFY(mCheckDKIMWhenOnlyTesting);
    QVERIFY(!mCheckDKIMWhenOnlyTesting->text().isEmpty());

    QCheckBox *mUseAuthenticationResultRelaxedParser = w.findChild<QCheckBox *>(QStringLiteral("mUseAuthenticationResultRelaxedParser"));
    QVERIFY(mUseAuthenticationResultRelaxedParser);
    QVERIFY(!mUseAuthenticationResultRelaxedParser->text().isEmpty());

    QComboBox *mSha1Policy = w.findChild<QComboBox *>(QStringLiteral("rsa1-policy"));
    QVERIFY(mSha1Policy);
    QVERIFY(mSha1Policy->count() > 0);

    QComboBox *mSmallKeyPolicy = w.findChild<QComboBox *>(QStringLiteral("mSmallKeyPolicy"));
    QVERIFY(mSmallKeyPolicy);
    QVERIFY(mSmallKeyPolicy->count() > 0);
}
