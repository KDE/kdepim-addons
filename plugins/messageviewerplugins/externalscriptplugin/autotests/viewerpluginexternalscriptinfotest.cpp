/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptinfotest.h"
#include "../viewerpluginexternalscriptinfo.h"

#include <QTest>

ViewerPluginExternalScriptInfoTest::ViewerPluginExternalScriptInfoTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalScriptInfoTest::~ViewerPluginExternalScriptInfoTest() = default;

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

#include "moc_viewerpluginexternalscriptinfotest.cpp"
