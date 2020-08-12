/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatenotetest.h"
#include "../createnoteplugin/viewerplugincreatenote.h"
#include <KActionCollection>
#include <QHBoxLayout>
#include <QTest>
#include <QStandardItemModel>
#include <MessageViewer/ViewerPluginInterface>

namespace MessageViewer {
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_noteEditStubModel;
}

ViewerPluginCreateNoteTest::ViewerPluginCreateNoteTest(QObject *parent)
    : QObject(parent)
{
    QStandardItemModel *model = new QStandardItemModel;
    MessageViewer::_k_noteEditStubModel = model;
}

ViewerPluginCreateNoteTest::~ViewerPluginCreateNoteTest()
{
}

void ViewerPluginCreateNoteTest::shouldCreateAction()
{
    MessageViewer::ViewerPluginCreatenote *note = new MessageViewer::ViewerPluginCreatenote(this);
    QVERIFY(!note->viewerPluginName().isEmpty());
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateNoteTest::shouldShowWidget()
{
    MessageViewer::ViewerPluginCreatenote *note = new MessageViewer::ViewerPluginCreatenote(this);
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    interface->execute();
    QWidget *createnotewidget = parent->findChild<QWidget *>(QStringLiteral("noteedit"));
    QVERIFY(createnotewidget);
    QCOMPARE(createnotewidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateNoteTest)
