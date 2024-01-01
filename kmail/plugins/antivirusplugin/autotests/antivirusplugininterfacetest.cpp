/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antivirusplugininterfacetest.h"
#include "../antivirusplugininterface.h"
#include <KActionCollection>
#include <QSignalSpy>
#include <QTest>

AntiVirusPluginInterfaceTest::AntiVirusPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AntiVirusPluginInterfaceTest::~AntiVirusPluginInterfaceTest() = default;

void AntiVirusPluginInterfaceTest::shouldHaveDefaultValue()
{
    AntiVirusPluginInterface interface;
    QVERIFY(!interface.parentWidget());
    QCOMPARE(interface.actionTypes().count(), 0);
}

void AntiVirusPluginInterfaceTest::shouldCreateAction()
{
    AntiVirusPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QCOMPARE(interface.actionTypes().count(), 1);
    QVERIFY(interface.actionTypes().at(0).action());
}

void AntiVirusPluginInterfaceTest::shouldEmitActivatedSignal()
{
    AntiVirusPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, &PimCommon::AbstractGenericPluginInterface::emitPluginActivated);
    interface.actionTypes().at(0).action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(AntiVirusPluginInterfaceTest)

#include "moc_antivirusplugininterfacetest.cpp"
