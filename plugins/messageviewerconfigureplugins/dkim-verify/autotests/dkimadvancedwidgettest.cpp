/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimadvancedwidgettest.h"
#include "dkimadvancedwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(DKIMAdvancedWidgetTest)

DKIMAdvancedWidgetTest::DKIMAdvancedWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMAdvancedWidgetTest::shouldHaveDefaultValues()
{
    DKIMAdvancedWidget w;
    const auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    const auto mCheckDKIMWhenOnlyTesting = w.findChild<QCheckBox *>(u"kcfg_VerifySignatureWhenOnlyTest"_s);
    QVERIFY(mCheckDKIMWhenOnlyTesting);
    QVERIFY(!mCheckDKIMWhenOnlyTesting->text().isEmpty());

    const auto mUseAuthenticationResultRelaxedParser = w.findChild<QCheckBox *>(u"kcfg_UseRelaxedParsingAuthenticationResults"_s);
    QVERIFY(mUseAuthenticationResultRelaxedParser);
    QVERIFY(!mUseAuthenticationResultRelaxedParser->text().isEmpty());

    const auto mSha1Policy = w.findChild<QComboBox *>(u"kcfg_PolicyRsaSha1"_s);
    QVERIFY(mSha1Policy);
    QVERIFY(mSha1Policy->count() > 0);

    const auto mSmallKeyPolicy = w.findChild<QComboBox *>(u"kcfg_PublicRsaTooSmall"_s);
    QVERIFY(mSmallKeyPolicy);
    QVERIFY(mSmallKeyPolicy->count() > 0);
}

#include "moc_dkimadvancedwidgettest.cpp"
