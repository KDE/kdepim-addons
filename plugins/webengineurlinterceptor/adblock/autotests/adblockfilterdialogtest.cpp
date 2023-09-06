/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockfilterdialogtest.h"
#include "adblockfilterdialog.h"
#include "adblockfilterwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AdblockFilterDialogTest)
AdblockFilterDialogTest::AdblockFilterDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AdblockFilterDialogTest::shouldHaveDefaultValues()
{
    AdblockFilterDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mAdblockFilterWidget = w.findChild<AdblockFilterWidget *>(QStringLiteral("mAdblockFilterWidget"));
    QVERIFY(mAdblockFilterWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}
