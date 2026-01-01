/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "headerstylepluginmanagertest.h"
#include <KActionCollection>
#include <MessageViewer/HeaderStyleMenuManager>
#include <QTest>

HeaderStylePluginManagerTest::HeaderStylePluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

HeaderStylePluginManagerTest::~HeaderStylePluginManagerTest() = default;

void HeaderStylePluginManagerTest::shouldHaveDefaultValue()
{
    MessageViewer::HeaderStyleMenuManager menu(new KActionCollection(this));
    QVERIFY(menu.menu());
}

QTEST_MAIN(HeaderStylePluginManagerTest)

#include "moc_headerstylepluginmanagertest.cpp"
