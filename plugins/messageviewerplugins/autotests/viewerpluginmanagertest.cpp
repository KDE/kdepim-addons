/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "viewerpluginmanagertest.h"
#include "messageviewer/viewerpluginmanager.h"
#include <QTest>

ViewerPluginManagerTest::ViewerPluginManagerTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginManagerTest::~ViewerPluginManagerTest()
{
}

void ViewerPluginManagerTest::shouldHaveDefaultValue()
{
    MessageViewer::ViewerPluginManager *manager = new MessageViewer::ViewerPluginManager(this);
    manager->setPluginName(QStringLiteral("messageviewer"));
    manager->setPluginDirectory(QStringLiteral("messageviewer/viewerplugin"));
    QVERIFY(manager->initializePluginList());
    QVERIFY(!manager->pluginsList().isEmpty());
}

QTEST_MAIN(ViewerPluginManagerTest)
