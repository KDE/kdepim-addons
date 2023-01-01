/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidgettest.h"
#include "dkimadvancedwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QTest>
QTEST_MAIN(DKIMAdvancedWidgetTest)

DKIMAdvancedWidgetTest::DKIMAdvancedWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMAdvancedWidgetTest::shouldHaveDefaultValues()
{
    DKIMAdvancedWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mCheckDKIMWhenOnlyTesting = w.findChild<QCheckBox *>(QStringLiteral("mCheckDKIMWhenOnlyTesting"));
    QVERIFY(mCheckDKIMWhenOnlyTesting);
    QVERIFY(!mCheckDKIMWhenOnlyTesting->text().isEmpty());

    auto mUseAuthenticationResultRelaxedParser = w.findChild<QCheckBox *>(QStringLiteral("mUseAuthenticationResultRelaxedParser"));
    QVERIFY(mUseAuthenticationResultRelaxedParser);
    QVERIFY(!mUseAuthenticationResultRelaxedParser->text().isEmpty());

    auto mSha1Policy = w.findChild<QComboBox *>(QStringLiteral("rsa1-policy"));
    QVERIFY(mSha1Policy);
    QVERIFY(mSha1Policy->count() > 0);

    auto mSmallKeyPolicy = w.findChild<QComboBox *>(QStringLiteral("mSmallKeyPolicy"));
    QVERIFY(mSmallKeyPolicy);
    QVERIFY(mSmallKeyPolicy->count() > 0);
}
