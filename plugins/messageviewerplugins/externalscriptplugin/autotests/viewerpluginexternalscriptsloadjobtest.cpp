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

#include "viewerpluginexternalscriptsloadjobtest.h"
#include "../viewerpluginexternalscriptsloadjob.h"

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
    QVERIFY(job.externalScriptsDirectories().isEmpty());
}

void ViewerPluginExternalScriptsLoadJobTest::shouldAssignDirectory()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = QStringList() << QStringLiteral("test_dir");
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldLoadDataInfo()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = { QLatin1String(TEST_DATA_DIR) + QStringLiteral("/correctdesktop/")};
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 1);
    ViewerPluginExternalScriptInfo info = job.scriptInfos().first();
    QCOMPARE(info.commandLine(), QStringLiteral("foo-bla"));
    QCOMPARE(info.name(), QStringLiteral("foo"));
    QCOMPARE(info.description(), QStringLiteral("description"));
    QCOMPARE(info.executable(), QStringLiteral("bla"));
    QCOMPARE(info.icon(), QStringLiteral("blo"));
    QVERIFY(!info.isReadOnly());
    const QString filenamepath = QStringLiteral(TEST_DATA_DIR) + QStringLiteral("/correctdesktop/first.desktop");
    QCOMPARE(info.fileName(), filenamepath);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadEmptyDesktop()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = { QLatin1String(TEST_DATA_DIR) + QStringLiteral("/emptydesktop/") };
    job.setExternalScriptsDirectories(dirs);

    QDir directory(dirs.at(0));
    QVERIFY(directory.exists());
    const QDir::Filters filters = QDir::Files | QDir::Hidden | QDir::NoSymLinks;
    const QFileInfoList list = directory.entryInfoList(QStringList() << QStringLiteral("*.desktop"), filters);
    const int listSize(list.size());
    QCOMPARE(listSize, 1);

    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 0);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadNoNameDesktop()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = { QLatin1String(TEST_DATA_DIR) + QStringLiteral("/nonamedesktop/") };
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 0);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldLoadTwoDifferentDesktopFile()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = { QLatin1String(TEST_DATA_DIR) + QStringLiteral("/twodesktopfiles/") };
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 2);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadTwoSameNameDesktopFile()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = { QLatin1String(TEST_DATA_DIR) + QStringLiteral("/twosamenamedesktopfiles/") };
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 2);
}

QTEST_MAIN(ViewerPluginExternalScriptsLoadJobTest)
