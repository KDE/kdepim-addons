/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfiltertreeviewtest.h"
#include "adblockfiltertreeview.h"
#include <QTest>
QTEST_MAIN(AdblockFilterTreeViewTest)
AdblockFilterTreeViewTest::AdblockFilterTreeViewTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockFilterTreeViewTest::shouldHaveDefaultValues()
{
    AdblockFilterTreeView w;
    QVERIFY(!w.rootIsDecorated());
    QCOMPARE(w.contextMenuPolicy(), Qt::DefaultContextMenu);
    QVERIFY(w.isSortingEnabled());
}

#include "moc_adblockfiltertreeviewtest.cpp"
