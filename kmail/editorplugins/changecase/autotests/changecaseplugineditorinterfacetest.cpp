/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "changecaseplugineditorinterfacetest.h"
#include "../changecaseplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

ChangeCasePluginEditorInterfaceTest::ChangeCasePluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ChangeCasePluginEditorInterfaceTest::~ChangeCasePluginEditorInterfaceTest()
{
}

void ChangeCasePluginEditorInterfaceTest::shouldHaveDefaultValues()
{
    ChangeCasePluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::ActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::ActionType::Edit);
}

QTEST_MAIN(ChangeCasePluginEditorInterfaceTest)
