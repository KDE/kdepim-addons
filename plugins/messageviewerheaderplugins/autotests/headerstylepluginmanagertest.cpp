/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "headerstylepluginmanagertest.h"
#include "headerstylemenumanager.h"
#include <KActionCollection>
#include <QTest>

HeaderStylePluginManagerTest::HeaderStylePluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

HeaderStylePluginManagerTest::~HeaderStylePluginManagerTest()
{
}

void HeaderStylePluginManagerTest::shouldHaveDefaultValue()
{
    MessageViewer::HeaderStyleMenuManager menu(new KActionCollection(this));
    QVERIFY(menu.menu());
}

QTEST_MAIN(HeaderStylePluginManagerTest)
