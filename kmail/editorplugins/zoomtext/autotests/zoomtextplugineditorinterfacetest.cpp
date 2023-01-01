/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditorinterfacetest.h"
#include "../zoomtextplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

ZoomTextPluginEditorInterfaceTest::ZoomTextPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ZoomTextPluginEditorInterfaceTest::~ZoomTextPluginEditorInterfaceTest() = default;

void ZoomTextPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    ZoomTextPluginEditorInterface interface(nullptr);
    auto ac = new KActionCollection(this);
    interface.createAction(ac);
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::View);
    QVERIFY(ac->action(QStringLiteral("zoom_menu")));
    QVERIFY(ac->action(QStringLiteral("zoom_in")));
    QVERIFY(ac->action(QStringLiteral("zoom_out")));
    QVERIFY(ac->action(QStringLiteral("zoom_reset")));
}

QTEST_MAIN(ZoomTextPluginEditorInterfaceTest)
