/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "inserttemplatecommandplugineditorinterfacetest.h"
#include "../inserttemplatecommandplugineditorinterface.h"
#include <KActionCollection>
#include <QTest>

InsertTemplateCommandPluginEditorInterfaceTest::InsertTemplateCommandPluginEditorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

InsertTemplateCommandPluginEditorInterfaceTest::~InsertTemplateCommandPluginEditorInterfaceTest()
{
}

void InsertTemplateCommandPluginEditorInterfaceTest::shouldHaveDefaultValue()
{
    InsertTemplateCommandPluginEditorInterface interface(nullptr);
    interface.createAction(new KActionCollection(this));
    MessageComposer::PluginActionType type = interface.actionType();
    QVERIFY(type.action());
    QCOMPARE(type.type(), MessageComposer::PluginActionType::ToolBar);
}

QTEST_MAIN(InsertTemplateCommandPluginEditorInterfaceTest)
