/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardsheaderstyleplugintest.h"
#include "../standardsheaderstyleplugin/standardsheaderstyleinterface.h"
#include "../standardsheaderstyleplugin/standardsheaderstyleplugin.h"
#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>
#include <QTest>

StandardsHeaderStylePluginTest::StandardsHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

StandardsHeaderStylePluginTest::~StandardsHeaderStylePluginTest() = default;

void StandardsHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::StandardsHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void StandardsHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::StandardsHeaderStylePlugin plugin;
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

QTEST_MAIN(StandardsHeaderStylePluginTest)

#include "moc_standardsheaderstyleplugintest.cpp"
