/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "antispamplugininterfacetest.h"
#include "../antispamplugininterface.h"
#include <KActionCollection>
#include <QTest>
#include <QAction>
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
    QVERIFY(!interface.actionType().action());
}

void AntiSpamPluginInterfaceTest::shouldCreateAction()
{
    AntiSpamPluginInterface interface;
    interface.createAction(new KActionCollection(this));
    QVERIFY(interface.actionType().action());
}

void AntiSpamPluginInterfaceTest::shouldEmitActivatedSignal()
{
    AntiSpamPluginInterface interface;
    interface.createAction(new KActionCollection(this));

    QSignalSpy spy1(&interface, SIGNAL(emitPluginActivated(PimCommon::GenericPluginInterface*)));
    interface.actionType().action()->trigger();
    QCOMPARE(spy1.count(), 1);
}

QTEST_MAIN(AntiSpamPluginInterfaceTest)
