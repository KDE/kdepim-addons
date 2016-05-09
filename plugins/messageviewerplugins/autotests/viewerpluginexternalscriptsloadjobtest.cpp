/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalscriptsloadjobtest.h"
#include "../externalscriptplugin/viewerpluginexternalscriptsloadjob.h"

#include <QTest>

ViewerPluginExternalScriptsLoadJobTest::ViewerPluginExternalScriptsLoadJobTest(QObject *parent)
    : QObject(parent)
{

}

ViewerPluginExternalScriptsLoadJobTest::~ViewerPluginExternalScriptsLoadJobTest()
{

}

void ViewerPluginExternalScriptsLoadJobTest::shouldHaveDefaultValues()
{
    ViewerPluginExternalScriptsLoadJob job;
    QVERIFY(job.scriptInfos().isEmpty());
    QVERIFY(job.externalScriptsDirectory().isEmpty());
}

void ViewerPluginExternalScriptsLoadJobTest::shouldAssignDirectory()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QString dir = QStringLiteral("test_dir");
    job.setExternalScriptsDirectory(dir);
    QCOMPARE(job.externalScriptsDirectory(), dir);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldLoadDataInfo()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QString dir = QLatin1String(TEST_DATA_DIR);
    job.setExternalScriptsDirectory(dir);
    QCOMPARE(job.externalScriptsDirectory(), dir);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 1);
    ViewerPluginExternalScriptInfo info = job.scriptInfos().first();
    QCOMPARE(info.commandLine(), QStringLiteral("foo-bla"));
    QCOMPARE(info.name(), QStringLiteral("foo"));
    QCOMPARE(info.description(), QStringLiteral("description"));
    QCOMPARE(info.executable(), QStringLiteral("bla"));
}

QTEST_MAIN(ViewerPluginExternalScriptsLoadJobTest)
