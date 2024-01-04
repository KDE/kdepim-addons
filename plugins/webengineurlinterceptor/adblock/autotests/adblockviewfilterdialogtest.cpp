/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterdialogtest.h"
#include "adblockviewfilterdialog.h"
#include <QTest>
QTEST_MAIN(AdblockViewFilterDialogTest)
AdblockViewFilterDialogTest::AdblockViewFilterDialogTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockViewFilterDialogTest::shouldHaveDefaultValues()
{
    AdblockViewFilterDialog d;
    // TODO
}

#include "moc_adblockviewfilterdialogtest.cpp"
