/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskitemtest.h"
#include "autogenerateconfigureaskitem.h"
#include <QTest>
QTEST_GUILESS_MAIN(AutogenerateConfigureAskItemTest)

AutogenerateConfigureAskItemTest::AutogenerateConfigureAskItemTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureAskItemTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskItem item;
    QVERIFY(item.enabled());
    QVERIFY(item.text().isEmpty());
}

#include "moc_autogenerateconfigureaskitemtest.cpp"
