/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginmanagertest.h"
#include <MessageViewer/ViewerPluginManager>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

ViewerPluginManagerTest::ViewerPluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginManagerTest::~ViewerPluginManagerTest() = default;

void ViewerPluginManagerTest::shouldHaveDefaultValue()
{
    auto manager = new MessageViewer::ViewerPluginManager(this);
    manager->setPluginName(u"messageviewer"_s);
    manager->setPluginDirectory(u"pim6/messageviewer/viewerplugin"_s);
    QVERIFY(manager->initializePluginList());
    QVERIFY(!manager->pluginsList().isEmpty());
}

QTEST_MAIN(ViewerPluginManagerTest)

#include "moc_viewerpluginmanagertest.cpp"
