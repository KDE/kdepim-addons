/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertemailplugineditorinterfacetest.h"
#include "../insertemailplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

InsertEmailPluginEditorInterfaceTest::InsertEmailPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

InsertEmailPluginEditorInterfaceTest::~InsertEmailPluginEditorInterfaceTest()
{
}

void InsertEmailPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    InsertEmailPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Edit);
}

QTEST_MAIN(InsertEmailPluginEditorInterfaceTest)
