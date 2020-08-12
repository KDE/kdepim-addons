/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatetodotest.h"
#include "../createtodoplugin/viewerplugincreatetodo.h"
#include <QTest>
#include <KActionCollection>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <MessageViewer/ViewerPluginInterface>

namespace MessageViewer {
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_todoEditStubModel;
}

ViewerPluginCreateTodoTest::ViewerPluginCreateTodoTest(QObject *parent)
    : QObject(parent)
{
    QStandardItemModel *model = new QStandardItemModel;
    MessageViewer::_k_todoEditStubModel = model;
}

ViewerPluginCreateTodoTest::~ViewerPluginCreateTodoTest()
{
}

void ViewerPluginCreateTodoTest::shouldCreateAction()
{
    MessageViewer::ViewerPluginCreatetodo *todo = new MessageViewer::ViewerPluginCreatetodo(this);
    QVERIFY(!todo->viewerPluginName().isEmpty());
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = todo->createView(parent, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateTodoTest::shouldShowWidget()
{
    MessageViewer::ViewerPluginCreatetodo *todo = new MessageViewer::ViewerPluginCreatetodo(this);
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = todo->createView(parent, new KActionCollection(this));
    interface->execute();
    QWidget *createtodowidget = parent->findChild<QWidget *>(QStringLiteral("todoedit"));
    QVERIFY(createtodowidget);
    QCOMPARE(createtodowidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateTodoTest)
