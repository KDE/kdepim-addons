/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatenotetest.h"
#include "../createnoteplugin/viewerplugincreatenote.h"
#include <KActionCollection>
#include <MessageViewer/ViewerPluginInterface>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

namespace MessageViewer
{
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_noteEditStubModel;
}

ViewerPluginCreateNoteTest::ViewerPluginCreateNoteTest(QObject *parent)
    : QObject(parent)
{
    auto model = new QStandardItemModel;
    MessageViewer::_k_noteEditStubModel = model;
}

ViewerPluginCreateNoteTest::~ViewerPluginCreateNoteTest() = default;

void ViewerPluginCreateNoteTest::shouldCreateAction()
{
    auto note = new MessageViewer::ViewerPluginCreatenote(this);
    QVERIFY(!note->viewerPluginName().isEmpty());
    auto parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateNoteTest::shouldShowWidget()
{
    auto note = new MessageViewer::ViewerPluginCreatenote(this);
    auto parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);
    MessageViewer::ViewerPluginInterface *interface = note->createView(parent, new KActionCollection(this));
    interface->execute();
    const auto createnotewidget = parent->findChild<QWidget *>(u"noteedit"_s);
    QVERIFY(createnotewidget);
    QCOMPARE(createnotewidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateNoteTest)

#include "moc_viewerplugincreatenotetest.cpp"
