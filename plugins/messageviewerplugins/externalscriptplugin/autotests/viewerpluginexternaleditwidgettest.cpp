/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "viewerpluginexternaleditwidgettest.h"
#include "../configuredialog/viewerpluginexternaleditwidget.h"
#include <KUrlRequester>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>

ViewerPluginExternalEditWidgetTest::ViewerPluginExternalEditWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalEditWidgetTest::~ViewerPluginExternalEditWidgetTest()
{
}

void ViewerPluginExternalEditWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditWidget w;
    QFormLayout *mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QLineEdit *mName = w.findChild<QLineEdit *>(QStringLiteral("name"));
    QVERIFY(mName);

    QLineEdit *mDescription = w.findChild<QLineEdit *>(QStringLiteral("description"));
    QVERIFY(mDescription);

    QLineEdit *mCommandLine = w.findChild<QLineEdit *>(QStringLiteral("commandline"));
    QVERIFY(mCommandLine);

    auto mExecutable = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mExecutable);
}

void ViewerPluginExternalEditWidgetTest::shouldGetSaveInfo_data()
{
    QTest::addColumn<ViewerPluginExternalScriptInfo>("scriptinfo");
    ViewerPluginExternalScriptInfo info;
    info.setCommandLine(QStringLiteral("foo"));
    info.setDescription(QStringLiteral("blo"));
    info.setExecutable(QStringLiteral("voo"));
    info.setName(QStringLiteral("bla"));
    QTest::newRow("test1") << info;

    info.setIsReadOnly(true);
    QTest::newRow("test2") << info;

    info.setFileName(QStringLiteral("lili"));
    QTest::newRow("test3") << info;
}

void ViewerPluginExternalEditWidgetTest::shouldGetSaveInfo()
{
    QFETCH(ViewerPluginExternalScriptInfo, scriptinfo);
    ViewerPluginExternalEditWidget w;
    w.setScriptInfo(scriptinfo);
    QCOMPARE(scriptinfo, w.scriptInfo());
}

QTEST_MAIN(ViewerPluginExternalEditWidgetTest)
