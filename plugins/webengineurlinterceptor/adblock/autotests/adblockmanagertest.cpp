/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanagertest.h"
#include "../lib/adblockmanager.h"
#include <QStandardPaths>
#include <QTest>

AdblockManagerTest::AdblockManagerTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AdblockManagerTest::~AdblockManagerTest() = default;

void AdblockManagerTest::shouldHaveDefaultValue()
{
    AdBlock::AdblockManager w;
    QVERIFY(!w.isEnabled());
}

QTEST_MAIN(AdblockManagerTest)
