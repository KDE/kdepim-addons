/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreateeventtest.h"
#include "../createeventplugin/viewerplugincreateevent.h"
#include <KActionCollection>
#include <MessageViewer/ViewerPluginInterface>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

namespace MessageViewer
{
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_eventEditStubModel;
}

ViewerPluginCreateeventTest::ViewerPluginCreateeventTest(QObject *parent)
    : QObject(parent)
{
    auto model = new QStandardItemModel;
    MessageViewer::_k_eventEditStubModel = model;
}

ViewerPluginCreateeventTest::~ViewerPluginCreateeventTest() = default;

void ViewerPluginCreateeventTest::shouldCreateAction()
{
    auto event = new MessageViewer::ViewerPluginCreateevent(this);
    QVERIFY(!event->viewerPluginName().isEmpty());
    auto parent = std::make_unique<QWidget>(nullptr);
    parent->setLayout(new QHBoxLayout);
    std::unique_ptr<MessageViewer::ViewerPluginInterface> interface(event->createView(parent.get(), new KActionCollection(this)));
    QVERIFY(interface);
    QVERIFY(!interface->actions().isEmpty());
}

void ViewerPluginCreateeventTest::shouldShowWidget()
{
    auto event = new MessageViewer::ViewerPluginCreateevent(this);
    auto parent = std::make_unique<QWidget>(nullptr);
    parent->setLayout(new QHBoxLayout);
    std::unique_ptr<MessageViewer::ViewerPluginInterface> interface(event->createView(parent.get(), new KActionCollection(this)));
    interface->execute();
    const auto createeventwidget = parent->findChild<QWidget *>(u"eventedit"_s);
    QVERIFY(createeventwidget);
    QCOMPARE(createeventwidget->isHidden(), false);
}

QTEST_MAIN(ViewerPluginCreateeventTest)

#include "moc_viewerplugincreateeventtest.cpp"
