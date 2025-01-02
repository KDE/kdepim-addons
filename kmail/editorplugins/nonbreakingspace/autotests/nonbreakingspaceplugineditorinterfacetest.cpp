/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nonbreakingspaceplugineditorinterfacetest.h"
#include "../nonbreakingspaceplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

NonBreakingSpacePluginEditorInterfaceTest::NonBreakingSpacePluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

NonBreakingSpacePluginEditorInterfaceTest::~NonBreakingSpacePluginEditorInterfaceTest() = default;

void NonBreakingSpacePluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    NonBreakingSpacePluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Insert);
}

QTEST_MAIN(NonBreakingSpacePluginEditorInterfaceTest)

#include "moc_nonbreakingspaceplugineditorinterfacetest.cpp"
