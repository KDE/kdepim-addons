/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblocklistsutiltest.h"
#include "adblocklistsutil.h"
#include <QTest>
QTEST_GUILESS_MAIN(AdblockListsUtilTest)
AdblockListsUtilTest::AdblockListsUtilTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockListsUtilTest::shouldVerifyList()
{
    QVERIFY(!AdblockListsUtil::adblockFilterNamesDefaultList().isEmpty());
    QVERIFY(!AdblockListsUtil::adblockFilterUrlsDefaultList().isEmpty());

    QCOMPARE(AdblockListsUtil::adblockFilterNamesDefaultList().count(), AdblockListsUtil::adblockFilterUrlsDefaultList().count());
}
