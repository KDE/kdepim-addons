/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "enterpriseheaderstyleplugintest.h"
#include "../enterpriseheaderstyleplugin/enterpriseheaderstyleinterface.h"
#include "../enterpriseheaderstyleplugin/enterpriseheaderstyleplugin.h"
#include "utils.h"

#include <MessageViewer/HeaderStyle>

#include <KActionCollection>
#include <KActionMenu>
#include <QActionGroup>
#include <QTest>

EnterpriseHeaderStylePluginTest::EnterpriseHeaderStylePluginTest(QObject *parent)
    : QObject(parent)
{
}

EnterpriseHeaderStylePluginTest::~EnterpriseHeaderStylePluginTest() = default;

void EnterpriseHeaderStylePluginTest::shouldHaveDefaultValue()
{
    MessageViewer::EnterpriseHeaderStylePlugin plugin;
    QVERIFY(plugin.headerStyle());
    QVERIFY(plugin.headerStrategy());
}

void EnterpriseHeaderStylePluginTest::shouldCreateInterface()
{
    MessageViewer::EnterpriseHeaderStylePlugin plugin;
    auto menu = new KActionMenu(this);
    auto act = new QActionGroup(this);

    MessageViewer::HeaderStyleInterface *interface = plugin.createView(menu, act, new KActionCollection(this));
    QVERIFY(interface);
    QVERIFY(!interface->action().isEmpty());
    delete interface;
}

void EnterpriseHeaderStylePluginTest::testFormatEmpty()
{
    MessageViewer::EnterpriseHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = new KMime::Message();
    QString closedDiv = style->format(aMsg) + QStringLiteral("</div>");
    testHeaderFile(closedDiv, QStringLiteral("empty.enterprise"));
    delete aMsg;
}

void EnterpriseHeaderStylePluginTest::testFormat_data()
{
    QTest::addColumn<QString>("mailbox");

    QDir dir(QStringLiteral(HEADER_DATA_DIR));
    const auto l = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << file;
    }
}

void EnterpriseHeaderStylePluginTest::testFormat()
{
    QFETCH(QString, mailbox);

    MessageViewer::EnterpriseHeaderStylePlugin plugin;
    auto style = plugin.headerStyle();
    auto strategy = plugin.headerStrategy();
    style->setHeaderStrategy(strategy);
    QCOMPARE(style->headerStrategy(), strategy);
    auto aMsg = readAndParseMail(mailbox);
    QString closedDiv = style->format(aMsg.get()) + QStringLiteral("</div>");
    testHeaderFile(closedDiv, mailbox + QStringLiteral(".enterprise"));
}

QTEST_MAIN(EnterpriseHeaderStylePluginTest)

#include "moc_enterpriseheaderstyleplugintest.cpp"
