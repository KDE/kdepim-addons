/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditorinterfacetest.h"

#include "../zoomtextplugineditorinterface.h"
#include <KActionCollection>
#include <QStatusBar>
#include <QTest>

using namespace Qt::Literals::StringLiterals;

ZoomTextPluginEditorInterfaceTest::ZoomTextPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ZoomTextPluginEditorInterfaceTest::~ZoomTextPluginEditorInterfaceTest() = default;

void ZoomTextPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    ZoomTextPluginEditorInterface interface(nullptr);
    auto ac = std::make_unique<KActionCollection>(this);
    interface.createAction(ac.get());
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::View);
    QVERIFY(ac->action(u"zoom_menu"_s));
    QVERIFY(ac->action(u"zoom_in"_s));
    QVERIFY(ac->action(u"zoom_out"_s));
    QVERIFY(ac->action(u"zoom_reset"_s));

    QStatusBar statusBar;
    statusBar.addPermanentWidget(interface.statusBarWidget());
}

QTEST_MAIN(ZoomTextPluginEditorInterfaceTest)

#include "moc_zoomtextplugineditorinterfacetest.cpp"
