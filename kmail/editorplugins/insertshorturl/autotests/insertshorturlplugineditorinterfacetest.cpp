/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlplugineditorinterfacetest.h"
#include "../insertshorturlplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

InsertShorturlPluginEditorInterfaceTest::InsertShorturlPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

InsertShorturlPluginEditorInterfaceTest::~InsertShorturlPluginEditorInterfaceTest() = default;

void InsertShorturlPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    InsertShorturlPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::PopupMenu);
}

QTEST_MAIN(InsertShorturlPluginEditorInterfaceTest)

#include "moc_insertshorturlplugineditorinterfacetest.cpp"
