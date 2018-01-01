/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalscriptinfotest.h"
#include "../viewerpluginexternalscriptinfo.h"

#include <QTest>

ViewerPluginExternalScriptInfoTest::ViewerPluginExternalScriptInfoTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalScriptInfoTest::~ViewerPluginExternalScriptInfoTest()
{
}

void ViewerPluginExternalScriptInfoTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalScriptInfo info;
    QVERIFY(info.name().isEmpty());
    QVERIFY(info.commandLine().isEmpty());
    QVERIFY(info.executable().isEmpty());
    QVERIFY(info.description().isEmpty());
    QVERIFY(info.icon().isEmpty());
    QVERIFY(!info.isValid());
    QVERIFY(!info.isReadOnly());
}

void ViewerPluginExternalScriptInfoTest::shouldHaveValid()
{
    ViewerPluginExternalScriptInfo info;
    info.setName(QString());
    QVERIFY(!info.isValid());
    info.setName(QStringLiteral("foo"));
    info.setExecutable(QStringLiteral("bla"));
    QVERIFY(info.isValid());
    info.setName(QStringLiteral(" "));
    QVERIFY(!info.isValid());
    info.setName(QStringLiteral("foo"));
    info.setExecutable(QStringLiteral(" "));
    QVERIFY(!info.isValid());
}

void ViewerPluginExternalScriptInfoTest::shouldBeEqual_data()
{
    QTest::addColumn<ViewerPluginExternalScriptInfo>("scriptinfo");
    QTest::newRow("empty") << ViewerPluginExternalScriptInfo();

    ViewerPluginExternalScriptInfo f;
    f.setCommandLine(QStringLiteral("dd"));
    f.setDescription(QStringLiteral("bla"));
    f.setIsReadOnly(true);
    QTest::newRow("not-empty-1") << f;
    f.setExecutable(QStringLiteral("ssss"));
    QTest::newRow("not-empty-2") << f;
    f.setIcon(QStringLiteral("bloblo"));
    QTest::newRow("not-empty-3") << f;
}

void ViewerPluginExternalScriptInfoTest::shouldBeEqual()
{
    QFETCH(ViewerPluginExternalScriptInfo, scriptinfo);
    ViewerPluginExternalScriptInfo f;
    f = scriptinfo;
    QCOMPARE(f, scriptinfo);
}

QTEST_MAIN(ViewerPluginExternalScriptInfoTest)
