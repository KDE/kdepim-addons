/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockmanagertest.h"
#include "adblockmanager.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(AdblockManagerTest)
AdblockManagerTest::AdblockManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AdblockManagerTest::shouldHaveDefaultValues()
{
    AdblockManager m;
    QVERIFY(m.adblockFilterLists().isEmpty());
}

#include "moc_adblockmanagertest.cpp"
