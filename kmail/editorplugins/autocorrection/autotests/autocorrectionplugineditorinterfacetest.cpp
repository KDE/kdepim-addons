/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionplugineditorinterfacetest.h"
#include "../autocorrectionplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

AutoCorrectionPluginEditorInterfaceTest::AutoCorrectionPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AutoCorrectionPluginEditorInterfaceTest::~AutoCorrectionPluginEditorInterfaceTest()
{
}

void AutoCorrectionPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    AutoCorrectionPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::Tools);
}

QTEST_MAIN(AutoCorrectionPluginEditorInterfaceTest)
