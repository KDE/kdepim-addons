/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertspecialcharacterplugineditorinterfacetest.h"
#include "../insertspecialcharacterplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

InsertSpecialCharacterPluginEditorInterfaceTest::InsertSpecialCharacterPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

InsertSpecialCharacterPluginEditorInterfaceTest::~InsertSpecialCharacterPluginEditorInterfaceTest()
{
}

void InsertSpecialCharacterPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    InsertSpecialCharacterPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Edit);
}

QTEST_MAIN(InsertSpecialCharacterPluginEditorInterfaceTest)
