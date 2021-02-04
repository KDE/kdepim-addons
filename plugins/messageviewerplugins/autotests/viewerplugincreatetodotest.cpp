/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatetodotest.h"
#include "../createtodoplugin/viewerplugincreatetodo.h"
#include <KActionCollection>
#include <MessageViewer/ViewerPluginInterface>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QTest>

namespace MessageViewer
{
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_todoEditStubModel;
}

ViewerPluginCreateTodoTest::ViewerPluginCreateTodoTest(QObject *parent)
    : QObject(parent)
{
    auto model = new QStandardItemModel;
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
    auto *createtodowidget = parent->findChild<QWidget *>(QStringLiteral("todoedit"));
    QVERIFY(createtodowidget);
    QCOMPARE(createtodowidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateTodoTest)
