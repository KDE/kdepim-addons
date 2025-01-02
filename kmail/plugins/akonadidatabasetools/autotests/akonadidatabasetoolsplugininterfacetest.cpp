/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolsplugininterfacetest.h"
#include "../akonadidatabasetoolsplugininterface.h"
#include <KActionCollection>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(AkonadiDatabaseToolsPluginInterfaceTest)
AkonadiDatabaseToolsPluginInterfaceTest::AkonadiDatabaseToolsPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AkonadiDatabaseToolsPluginInterfaceTest::~AkonadiDatabaseToolsPluginInterfaceTest() = default;

void AkonadiDatabaseToolsPluginInterfaceTest::shouldHaveDefaultValue()
{
    AkonadiDatabaseToolsPluginInterface interface;
    QVERIFY(!interface.parentWidget());
    QCOMPARE(interface.actionTypes().count(), 0);
}

void AkonadiDatabaseToolsPluginInterfaceTest::shouldCreateAction()
{
    AkonadiDatabaseToolsPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QCOMPARE(interface.actionTypes().count(), 2);
    QVERIFY(interface.actionTypes().at(0).action());
    QVERIFY(interface.actionTypes().at(1).action());
}

#if 0 // We have some kmessagebox
void AkonadiDatabaseToolsPluginInterfaceTest::shouldEmitActivatedSignal()
{
    AkonadiDatabaseToolsPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, &PimCommon::AbstractGenericPluginInterface::emitPluginActivated);
    interface.actionTypes().at(0).action()->trigger();
    QCOMPARE(spy1.count(), 1);
}
#endif

#include "moc_akonadidatabasetoolsplugininterfacetest.cpp"
