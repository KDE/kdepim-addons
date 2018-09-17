/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "viewerplugincreateeventtest.h"
#include "../createeventplugin/viewerplugincreateevent.h"
#include <KActionCollection>
#include <QTest>
#include <QStandardItemModel>
#include <messageviewer/viewerplugininterface.h>
#include <QHBoxLayout>

namespace MessageViewer {
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_eventEditStubModel;
}

ViewerPluginCreateeventTest::ViewerPluginCreateeventTest(QObject *parent)
    : QObject(parent)
{
    QStandardItemModel *model = new QStandardItemModel;
    MessageViewer::_k_eventEditStubModel = model;
}

ViewerPluginCreateeventTest::~ViewerPluginCreateeventTest()
{
}

void ViewerPluginCreateeventTest::shouldCreateAction()
{
    MessageViewer::ViewerPluginCreateevent *event = new MessageViewer::ViewerPluginCreateevent(this);
    QVERIFY(!event->viewerPluginName().isEmpty());
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = event->createView(parent, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateeventTest::shouldShowWidget()
{
    MessageViewer::ViewerPluginCreateevent *event = new MessageViewer::ViewerPluginCreateevent(this);
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = event->createView(parent, new KActionCollection(this));
    interface->execute();
    QWidget *createeventwidget = parent->findChild<QWidget *>(QStringLiteral("eventedit"));
    QVERIFY(createeventwidget);
    QCOMPARE(createeventwidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateeventTest)
