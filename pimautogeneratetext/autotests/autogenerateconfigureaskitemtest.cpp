/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskitemtest.h"
#include "autogenerateconfigureaskinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(AutogenerateConfigureAskItemTest)

AutogenerateConfigureAskItemTest::AutogenerateConfigureAskItemTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureAskItemTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskInfo item;
    QVERIFY(item.enabled());
    QVERIFY(item.text().isEmpty());
    QVERIFY(item.title().isEmpty());
}

#include "moc_autogenerateconfigureaskitemtest.cpp"
