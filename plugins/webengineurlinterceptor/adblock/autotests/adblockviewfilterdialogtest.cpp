/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterdialogtest.h"
#include "adblockviewfilterdialog.h"
#include "adblockviewfilterwidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(AdblockViewFilterDialogTest)
AdblockViewFilterDialogTest::AdblockViewFilterDialogTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockViewFilterDialogTest::shouldHaveDefaultValues()
{
    AdblockViewFilterDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mAdblockViewFilterWidget = w.findChild<AdblockViewFilterWidget *>(QStringLiteral("mAdblockViewFilterWidget"));
    QVERIFY(mAdblockViewFilterWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}

#include "moc_adblockviewfilterdialogtest.cpp"
