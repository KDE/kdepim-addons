/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "logactivitiesplugininterfacetest.h"
#include "../logactivitiesplugininterface.h"
#include <KActionCollection>
#include <QTest>
#include <QSignalSpy>

LogActivitiesPluginInterfaceTest::LogActivitiesPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{

}

LogActivitiesPluginInterfaceTest::~LogActivitiesPluginInterfaceTest()
{

}

void LogActivitiesPluginInterfaceTest::shouldHaveDefaultValue()
{
    LogActivitiesPluginInterface interface;
    QVERIFY(!interface.parentWidget());
    QVERIFY(!interface.actionType().action());
}

void LogActivitiesPluginInterfaceTest::shouldCreateAction()
{
    LogActivitiesPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QVERIFY(interface.actionType().action());
}

void LogActivitiesPluginInterfaceTest::shouldEmitActivatedSignal()
{
    LogActivitiesPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, SIGNAL(emitPluginActivated(PimCommon::AbstractGenericPluginInterface*)));
    interface.actionType().action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(LogActivitiesPluginInterfaceTest)
