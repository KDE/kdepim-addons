/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardsheaderstyleplugintest.h"
#include "../standardsheaderstyleplugin/standardsheaderstyleplugin.h"
#include "../standardsheaderstyleplugin/standardsheaderstyleinterface.h"
#include <QTest>
#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>

StandardsHeaderStylePluginTest::StandardsHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

StandardsHeaderStylePluginTest::~StandardsHeaderStylePluginTest()
{
}

void StandardsHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::StandardsHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void StandardsHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::StandardsHeaderStylePlugin plugin;
    KActionMenu *menu = new KActionMenu(this);
    QActionGroup *act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

QTEST_MAIN(StandardsHeaderStylePluginTest)
