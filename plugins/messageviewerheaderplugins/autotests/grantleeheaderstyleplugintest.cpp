/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeheaderstyleplugintest.h"
#include "../grantleeheaderstyleplugin/grantleeheaderstyleinterface.h"
#include "../grantleeheaderstyleplugin/grantleeheaderstyleplugin.h"
#include "utils.h"

#include <GrantleeTheme/GrantleeThemeManager>
#include <MessageViewer/HeaderStyle>
#include <MimeTreeParser/NodeHelper>

#include <QActionGroup>
#include <QStandardPaths>
#include <QTest>

#include <KActionCollection>
#include <KActionMenu>

#ifndef Q_OS_WIN
void initLocale()
{
    setenv("LC_ALL", "C", 1);
    setenv("TZ", "UTC", 1);
    QLocale::setDefault(QLocale::c());
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

GrantleeHeaderStylePluginTest::GrantleeHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

GrantleeHeaderStylePluginTest::~GrantleeHeaderStylePluginTest() = default;

void GrantleeHeaderStylePluginTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
    expectedDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    expectedDataLocation += QStringLiteral("/messageviewer/themes");
    QDir targetDir(expectedDataLocation);
    QDir sourceDir(QStringLiteral(GRANTLEETHEME_DATA_DIR));
    const auto themeDirs = sourceDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    if (targetDir.exists()) {
        QVERIFY(targetDir.removeRecursively()); // Start with a fresh copy
    }

    for (const auto &themeDir : themeDirs) {
        const QString &dirName = targetDir.filePath(themeDir.fileName());
        QVERIFY(targetDir.mkpath(themeDir.fileName()));
        const auto files = QDir(themeDir.absoluteFilePath()).entryInfoList(QDir::Files | QDir::Readable | QDir::NoSymLinks);
        qDebug() << dirName << files;
        for (const auto &file : files) {
            const QString &newPath = dirName + QLatin1Char('/') + file.fileName();
            qDebug() << file << newPath;
            QVERIFY(QFile(file.absoluteFilePath()).copy(newPath));
        }
    }
}

void GrantleeHeaderStylePluginTest::cleanupTestCase()
{
    QDir targetDir(expectedDataLocation);

    if (targetDir.exists()) {
        QVERIFY(targetDir.removeRecursively()); // Start with a fresh copy
    }
}

void GrantleeHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::GrantleeHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void GrantleeHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::GrantleeHeaderStylePlugin plugin;
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    // QVERIFY(!interface->action().isEmpty());
}

void GrantleeHeaderStylePluginTest::testThemeActivation_data()
{
    QTest::addColumn<QString>("themeName");

    QDir dir(QStringLiteral(GRANTLEETHEME_DATA_DIR));
    const auto themeDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &t : themeDirs) {
        QTest::newRow(t.fileName().toLatin1().constData()) << t.fileName();
    }
}

void GrantleeHeaderStylePluginTest::testThemeActivation()
{
    QFETCH(QString, themeName);

    MessageViewer::GrantleeHeaderStylePlugin plugin;
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::GrantleeHeaderStyleInterface *interface =
        static_cast<MessageViewer::GrantleeHeaderStyleInterface *>(plugin.createView(menu, act, new KActionCollection(this)));
    QVERIFY(interface);

    QVERIFY(interface->mThemeManager->themes().contains(themeName));

    const auto actions = act->actions();
    for (const auto &action : actions) {
        if (action->data() == themeName) {
            action->trigger();
            break;
        }
    }

    QCOMPARE(plugin.headerStyle()->theme().dirName(), themeName);
}

void GrantleeHeaderStylePluginTest::testThemeRender_data()
{
    QTest::addColumn<QString>("themeName");
    QTest::addColumn<QString>("mailFileName");

    QDir dir(QStringLiteral(HEADER_DATA_DIR));
    const auto themeDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    const auto l = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);

    for (const QFileInfo &t : themeDirs) {
        const QDir themeDir(t.absoluteFilePath());
        for (const QString &file : l) {
            if (!themeDir.exists(file + QStringLiteral(".html"))) {
                continue;
            }
            QTest::newRow(QString(themeDir.dirName() + QStringLiteral("-") + file).toLatin1().constData()) << themeDir.dirName() << file;
        }
    }
}

void GrantleeHeaderStylePluginTest::testThemeRender()
{
    QFETCH(QString, themeName);
    QFETCH(QString, mailFileName);

    auto aMsg = readAndParseMail(mailFileName);
    MessageViewer::GrantleeHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    MimeTreeParser::NodeHelper nodeHelper;
    style->setNodeHelper(&nodeHelper);
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::GrantleeHeaderStyleInterface *interface =
        static_cast<MessageViewer::GrantleeHeaderStyleInterface *>(plugin.createView(menu, act, new KActionCollection(this)));
    QVERIFY(interface);

    QVERIFY(interface->mThemeManager->themes().contains(themeName));

    const auto themes = interface->mThemeManager->themes();
    for (const auto &theme : themes) {
        if (theme.dirName() != themeName) {
            continue;
        }
        if (theme.absolutePath().startsWith(expectedDataLocation)) {
            style->setTheme(theme);
            break;
        }
    }

    QCOMPARE(style->theme().dirName(), themeName);
    // Make sure, that we do not load the same file from a different location.
    QVERIFY(style->theme().absolutePath().startsWith(expectedDataLocation));

    const QString data = style->format(aMsg.get());
    testHeaderFile(data, mailFileName, themeName);
}

QTEST_MAIN(GrantleeHeaderStylePluginTest)

#include "moc_grantleeheaderstyleplugintest.cpp"
