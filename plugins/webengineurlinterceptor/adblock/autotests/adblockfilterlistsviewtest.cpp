/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsviewtest.h"
#include "adblockfilterlistsview.h"
#include <QTest>
QTEST_MAIN(AdblockFilterListsViewTest)
AdblockFilterListsViewTest::AdblockFilterListsViewTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockFilterListsViewTest::shouldHaveDefaultValues()
{
    AdblockFilterListsView w;
    QVERIFY(!w.rootIsDecorated());
    QCOMPARE(w.contextMenuPolicy(), Qt::DefaultContextMenu);
}

#include "moc_adblockfilterlistsviewtest.cpp"
