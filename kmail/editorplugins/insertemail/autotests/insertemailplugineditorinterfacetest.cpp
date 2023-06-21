/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

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

InsertEmailPluginEditorInterfaceTest::~InsertEmailPluginEditorInterfaceTest() = default;

void InsertEmailPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    InsertEmailPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Insert);
}

QTEST_MAIN(InsertEmailPluginEditorInterfaceTest)

#include "moc_insertemailplugineditorinterfacetest.cpp"
