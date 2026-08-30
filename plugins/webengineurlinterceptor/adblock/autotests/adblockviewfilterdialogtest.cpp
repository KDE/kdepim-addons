/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterdialogtest.h"
#include "adblockviewfilterdialog.h"
#include "adblockviewfilterwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(AdblockViewFilterDialogTest)
AdblockViewFilterDialogTest::AdblockViewFilterDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AdblockViewFilterDialogTest::shouldHaveDefaultValues()
{
    AdblockViewFilterDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    const auto mAdblockViewFilterWidget = w.findChild<AdblockViewFilterWidget *>(u"mAdblockViewFilterWidget"_s);
    QVERIFY(mAdblockViewFilterWidget);

    const auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_adblockviewfilterdialogtest.cpp"
