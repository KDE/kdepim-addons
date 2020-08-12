/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

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

ZoomTextPluginEditorInterfaceTest::~ZoomTextPluginEditorInterfaceTest()
{
}

void ZoomTextPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    ZoomTextPluginEditorInterface interface(nullptr);
    KActionCollection *ac = new KActionCollection(this);
    interface.createAction(ac);
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Edit);
    QVERIFY(ac->action(QStringLiteral("zoom_menu")));
    QVERIFY(ac->action(QStringLiteral("zoom_in")));
    QVERIFY(ac->action(QStringLiteral("zoom_out")));
    QVERIFY(ac->action(QStringLiteral("zoom_reset")));
}

QTEST_MAIN(ZoomTextPluginEditorInterfaceTest)
