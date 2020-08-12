/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "briefheaderstyleplugintest.h"
#include "utils.h"
#include "../briefheaderstyleplugin/briefheaderstyleplugin.h"
#include "../briefheaderstyleplugin/briefheaderstyleinterface.h"

#include <MessageViewer/HeaderStyle>

#include <QTest>
#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>

BriefHeaderStylePluginTest::BriefHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

BriefHeaderStylePluginTest::~BriefHeaderStylePluginTest()
{
}

void BriefHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::BriefHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void BriefHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::BriefHeaderStylePlugin plugin;
    KActionMenu *menu = new KActionMenu(this);
    QActionGroup *act = new QActionGroup(this);
    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

void BriefHeaderStylePluginTest::testFormatEmpty()
{
    MessageViewer::BriefHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = new KMime::Message();
    testHeaderFile(style->format(aMsg), QStringLiteral("empty.brief"));
    delete aMsg;
}

void BriefHeaderStylePluginTest::testFormat_data()
{
    QTest::addColumn<QString>("mailbox");

    QDir dir(QStringLiteral(HEADER_DATA_DIR));
    const auto l = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << file;
    }
}

void BriefHeaderStylePluginTest::testFormat()
{
    QFETCH(QString, mailbox);

    MessageViewer::BriefHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = readAndParseMail(mailbox);
    testHeaderFile(style->format(aMsg.data()), mailbox+QStringLiteral(".brief"));
}

QTEST_MAIN(BriefHeaderStylePluginTest)
