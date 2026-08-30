/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptinfotest.h"
#include "../viewerpluginexternalscriptinfo.h"

#include <QTest>
using namespace Qt::Literals::StringLiterals;

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
    info.setName(u"foo"_s);
    info.setExecutable(u"bla"_s);
    QVERIFY(info.isValid());
    info.setName(u" "_s);
    QVERIFY(!info.isValid());
    info.setName(u"foo"_s);
    info.setExecutable(u" "_s);
    QVERIFY(!info.isValid());
}

void ViewerPluginExternalScriptInfoTest::shouldBeEqual_data()
{
    QTest::addColumn<ViewerPluginExternalScriptInfo>("scriptinfo");
    QTest::newRow("empty") << ViewerPluginExternalScriptInfo();

    ViewerPluginExternalScriptInfo f;
    f.setCommandLine(u"dd"_s);
    f.setDescription(u"bla"_s);
    f.setIsReadOnly(true);
    QTest::newRow("not-empty-1") << f;
    f.setExecutable(u"ssss"_s);
    QTest::newRow("not-empty-2") << f;
    f.setIcon(u"bloblo"_s);
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
