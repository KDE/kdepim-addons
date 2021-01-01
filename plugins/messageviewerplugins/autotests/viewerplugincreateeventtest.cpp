/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreateeventtest.h"
#include "../createeventplugin/viewerplugincreateevent.h"
#include <KActionCollection>
#include <QTest>
#include <QStandardItemModel>
#include <MessageViewer/ViewerPluginInterface>
#include <QHBoxLayout>

namespace MessageViewer {
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_eventEditStubModel;
}

ViewerPluginCreateeventTest::ViewerPluginCreateeventTest(QObject *parent)
    : QObject(parent)
{
    auto *model = new QStandardItemModel;
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
    auto *createeventwidget = parent->findChild<QWidget *>(QStringLiteral("eventedit"));
    QVERIFY(createeventwidget);
    QCOMPARE(createeventwidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateeventTest)
