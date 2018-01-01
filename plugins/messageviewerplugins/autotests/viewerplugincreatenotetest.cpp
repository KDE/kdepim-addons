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

#include "viewerplugincreatenotetest.h"
#include "../createnoteplugin/viewerplugincreatenote.h"
#include <KActionCollection>
#include <QHBoxLayout>
#include <QTest>
#include <QStandardItemModel>
#include <messageviewer/viewerplugininterface.h>

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
    QWidget *parent = new QWidget(0);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateNoteTest::shouldShowWidget()
{
    MessageViewer::ViewerPluginCreatenote *note = new MessageViewer::ViewerPluginCreatenote(this);
    QWidget *parent = new QWidget(0);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    interface->execute();
    QWidget *createnotewidget = parent->findChild<QWidget *>(QStringLiteral("noteedit"));
    QVERIFY(createnotewidget);
    QCOMPARE(createnotewidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateNoteTest)
