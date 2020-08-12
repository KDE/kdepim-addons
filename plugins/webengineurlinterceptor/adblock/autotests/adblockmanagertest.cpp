/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanagertest.h"
#include "../lib/adblockmanager.h"
#include <QTest>
#include <QStandardPaths>

AdblockManagerTest::AdblockManagerTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AdblockManagerTest::~AdblockManagerTest()
{
}

void AdblockManagerTest::shouldHaveDefaultValue()
{
    AdBlock::AdblockManager w;
    QVERIFY(!w.isEnabled());
}

QTEST_MAIN(AdblockManagerTest)
