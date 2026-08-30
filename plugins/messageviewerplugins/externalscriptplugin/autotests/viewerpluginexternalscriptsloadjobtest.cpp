/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptsloadjobtest.h"
#include "../viewerpluginexternalscriptsloadjob.h"

#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalScriptsLoadJobTest::ViewerPluginExternalScriptsLoadJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ViewerPluginExternalScriptsLoadJobTest::~ViewerPluginExternalScriptsLoadJobTest() = default;

void ViewerPluginExternalScriptsLoadJobTest::shouldHaveDefaultValues()
{
    ViewerPluginExternalScriptsLoadJob job;
    QVERIFY(job.scriptInfos().isEmpty());
    QVERIFY(job.externalScriptsDirectories().isEmpty());
}

void ViewerPluginExternalScriptsLoadJobTest::shouldAssignDirectory()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = QStringList() << u"test_dir"_s;
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldLoadDataInfo()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = {QLatin1StringView(TEST_DATA_DIR) + u"/correctdesktop/"_s};
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 1);
    const ViewerPluginExternalScriptInfo info = job.scriptInfos().constFirst();
    QCOMPARE(info.commandLine(), u"foo-bla"_s);
    QCOMPARE(info.name(), u"foo"_s);
    QCOMPARE(info.description(), u"description"_s);
    QCOMPARE(info.executable(), u"bla"_s);
    QCOMPARE(info.icon(), u"blo"_s);
    QVERIFY(!info.isReadOnly());
    const QString filenamepath = QStringLiteral(TEST_DATA_DIR) + u"/correctdesktop/first.desktop"_s;
    QCOMPARE(info.fileName(), filenamepath);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadEmptyDesktop()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = {QLatin1StringView(TEST_DATA_DIR) + u"/emptydesktop/"_s};
    job.setExternalScriptsDirectories(dirs);

    QDir directory(dirs.at(0));
    QVERIFY(directory.exists());
    const QDir::Filters filters = QDir::Files | QDir::Hidden | QDir::NoSymLinks;
    const QFileInfoList list = directory.entryInfoList(QStringList() << u"*.desktop"_s, filters);
    const int listSize(list.size());
    QCOMPARE(listSize, 1);

    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 0);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadNoNameDesktop()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = {QLatin1StringView(TEST_DATA_DIR) + u"/nonamedesktop/"_s};
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 0);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldLoadTwoDifferentDesktopFile()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = {QLatin1StringView(TEST_DATA_DIR) + u"/twodesktopfiles/"_s};
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 2);
}

void ViewerPluginExternalScriptsLoadJobTest::shouldNotLoadTwoSameNameDesktopFile()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList dirs = {QLatin1StringView(TEST_DATA_DIR) + u"/twosamenamedesktopfiles/"_s};
    job.setExternalScriptsDirectories(dirs);
    QCOMPARE(job.externalScriptsDirectories(), dirs);
    job.start();
    QCOMPARE(job.scriptInfos().count(), 2);
}

QTEST_MAIN(ViewerPluginExternalScriptsLoadJobTest)

#include "moc_viewerpluginexternalscriptsloadjobtest.cpp"
