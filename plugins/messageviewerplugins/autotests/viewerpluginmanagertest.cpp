/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginmanagertest.h"
#include <MessageViewer/ViewerPluginManager>
#include <QTest>

ViewerPluginManagerTest::ViewerPluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginManagerTest::~ViewerPluginManagerTest() = default;

void ViewerPluginManagerTest::shouldHaveDefaultValue()
{
    auto manager = new MessageViewer::ViewerPluginManager(this);
    manager->setPluginName(QStringLiteral("messageviewer"));
    manager->setPluginDirectory(QStringLiteral("pim6/messageviewer/viewerplugin"));
    QVERIFY(manager->initializePluginList());
    QVERIFY(!manager->pluginsList().isEmpty());
}

QTEST_MAIN(ViewerPluginManagerTest)

#include "moc_viewerpluginmanagertest.cpp"
