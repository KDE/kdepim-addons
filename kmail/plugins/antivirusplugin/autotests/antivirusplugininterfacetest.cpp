/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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

#include "antivirusplugininterfacetest.h"
#include "../antivirusplugininterface.h"
#include <KActionCollection>
#include <QTest>
#include <QSignalSpy>

AntiVirusPluginInterfaceTest::AntiVirusPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AntiVirusPluginInterfaceTest::~AntiVirusPluginInterfaceTest()
{
}

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
