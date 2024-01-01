/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditorinterfacetest.h"
#include "../changecaseplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

ChangeCasePluginEditorInterfaceTest::ChangeCasePluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ChangeCasePluginEditorInterfaceTest::~ChangeCasePluginEditorInterfaceTest() = default;

void ChangeCasePluginEditorInterfaceTest::shouldHaveDefaultValues()
{
    ChangeCasePluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Edit);
}

QTEST_MAIN(ChangeCasePluginEditorInterfaceTest)

#include "moc_changecaseplugineditorinterfacetest.cpp"
