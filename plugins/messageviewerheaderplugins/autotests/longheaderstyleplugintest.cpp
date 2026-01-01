/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "longheaderstyleplugintest.h"
#include "../longheaderstyleplugin/longheaderstyleinterface.h"
#include "../longheaderstyleplugin/longheaderstyleplugin.h"
#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>
#include <QTest>

LongHeaderStylePluginTest::LongHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

LongHeaderStylePluginTest::~LongHeaderStylePluginTest() = default;

void LongHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::LongHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void LongHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::LongHeaderStylePlugin plugin;
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

QTEST_MAIN(LongHeaderStylePluginTest)

#include "moc_longheaderstyleplugintest.cpp"
