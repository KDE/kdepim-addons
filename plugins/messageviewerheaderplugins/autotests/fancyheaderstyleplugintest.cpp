/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "fancyheaderstyleplugintest.h"
#include "utils.h"
#include "../fancyheaderstyleplugin/fancyheaderstyleplugin.h"
#include "../fancyheaderstyleplugin/fancyheaderstyleinterface.h"

#include <MessageViewer/HeaderStyle>

#include <QTest>
#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>

FancyHeaderStylePluginTest::FancyHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

FancyHeaderStylePluginTest::~FancyHeaderStylePluginTest()
{
}

void FancyHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::FancyHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void FancyHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::FancyHeaderStylePlugin plugin;
    KActionMenu *menu = new KActionMenu(this);
    QActionGroup *act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

void FancyHeaderStylePluginTest::testFormatEmpty()
{
    MessageViewer::FancyHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = new KMime::Message();
    testHeaderFile(style->format(aMsg), QStringLiteral("empty.fancy"));
    delete aMsg;
}

void FancyHeaderStylePluginTest::testFormat_data()
{
    QTest::addColumn<QString>("mailbox");

    QDir dir(QStringLiteral(HEADER_DATA_DIR));
    const auto l = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << file;
    }
}

void FancyHeaderStylePluginTest::testFormat()
{
    QFETCH(QString, mailbox);

    MessageViewer::FancyHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = readAndParseMail(mailbox);
    testHeaderFile(style->format(aMsg.data()), mailbox+QStringLiteral(".fancy"));
}

QTEST_MAIN(FancyHeaderStylePluginTest)
