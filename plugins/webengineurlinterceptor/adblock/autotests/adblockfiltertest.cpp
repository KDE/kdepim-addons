/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfiltertest.h"
#include "adblockfilter.h"
#include <QTest>
QTEST_GUILESS_MAIN(AdblockFilterTest)
AdblockFilterTest::AdblockFilterTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockFilterTest::shouldHaveDefaultValues()
{
    AdblockFilter f;
    QVERIFY(f.url().isEmpty());
    QVERIFY(f.name().isEmpty());
}

#include "moc_adblockfiltertest.cpp"
