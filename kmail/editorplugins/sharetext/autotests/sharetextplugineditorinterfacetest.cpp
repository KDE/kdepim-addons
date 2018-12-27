/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "sharetextplugineditorinterfacetest.h"
#include "../sharetextplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

ShareTextPluginEditorInterfaceTest::ShareTextPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

ShareTextPluginEditorInterfaceTest::~ShareTextPluginEditorInterfaceTest()
{
}

void ShareTextPluginEditorInterfaceTest::shouldHaveDefaultValues()
{
    ShareTextPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::File);
}

QTEST_MAIN(ShareTextPluginEditorInterfaceTest)
