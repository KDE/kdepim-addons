/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sharetextplugineditorinterfacetest.h"
using namespace Qt::Literals::StringLiterals;

#include "../sharetextplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

ShareTextPluginEditorInterfaceTest::ShareTextPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ShareTextPluginEditorInterfaceTest::~ShareTextPluginEditorInterfaceTest() = default;

void ShareTextPluginEditorInterfaceTest::shouldHaveDefaultValues()
{
    ShareTextPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::File);
}

QTEST_MAIN(ShareTextPluginEditorInterfaceTest)

#include "moc_sharetextplugineditorinterfacetest.cpp"
