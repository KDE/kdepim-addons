/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "antispamplugininterfacetest.h"
#include "../antispamplugininterface.h"
#include <KActionCollection>
#include <QTest>
#include <QSignalSpy>

AntiSpamPluginInterfaceTest::AntiSpamPluginInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AntiSpamPluginInterfaceTest::~AntiSpamPluginInterfaceTest()
{
}

void AntiSpamPluginInterfaceTest::shouldHaveDefaultValue()
{
    AntiSpamPluginInterface interface;
    QVERIFY(!interface.parentWidget());
    QVERIFY(!interface.actionTypes().at(0).action());
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

    QSignalSpy spy1(&interface, SIGNAL(emitPluginActivated(PimCommon::AbstractGenericPluginInterface*)));
    interface.actionTypes().at(0).action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(AntiSpamPluginInterfaceTest)
