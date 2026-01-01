/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antispamplugininterfacetest.h"
#include "../antispamplugininterface.h"
#include <KActionCollection>
#include <QSignalSpy>
#include <QTest>

AntiSpamPluginInterfaceTest::AntiSpamPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AntiSpamPluginInterfaceTest::~AntiSpamPluginInterfaceTest() = default;

void AntiSpamPluginInterfaceTest::shouldHaveDefaultValue()
{
    AntiSpamPluginInterface interface;
    QVERIFY(!interface.parentWidget());
    QVERIFY(interface.actionTypes().isEmpty());
}

void AntiSpamPluginInterfaceTest::shouldCreateAction()
{
    AntiSpamPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QCOMPARE(interface.actionTypes().count(), 1);
    QVERIFY(interface.actionTypes().at(0).action());
}

void AntiSpamPluginInterfaceTest::shouldEmitActivatedSignal()
{
    AntiSpamPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, &PimCommon::AbstractGenericPluginInterface::emitPluginActivated);
    interface.actionTypes().at(0).action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(AntiSpamPluginInterfaceTest)

#include "moc_antispamplugininterfacetest.cpp"
