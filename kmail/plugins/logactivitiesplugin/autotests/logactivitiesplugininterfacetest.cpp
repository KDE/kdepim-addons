/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitiesplugininterfacetest.h"
#include "../logactivitiesplugininterface.h"
#include <KActionCollection>
#include <QSignalSpy>
#include <QTest>

LogActivitiesPluginInterfaceTest::LogActivitiesPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

LogActivitiesPluginInterfaceTest::~LogActivitiesPluginInterfaceTest() = default;

void LogActivitiesPluginInterfaceTest::shouldHaveDefaultValue()
{
    LogActivitiesPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QVERIFY(!interface.parentWidget());
    QCOMPARE(interface.actionTypes().count(), 1);
    QVERIFY(interface.actionTypes().at(0).action());
}

void LogActivitiesPluginInterfaceTest::shouldCreateAction()
{
    LogActivitiesPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QVERIFY(interface.actionTypes().at(0).action());
}

void LogActivitiesPluginInterfaceTest::shouldEmitActivatedSignal()
{
    LogActivitiesPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, &PimCommon::AbstractGenericPluginInterface::emitPluginActivated);
    interface.actionTypes().at(0).action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(LogActivitiesPluginInterfaceTest)
