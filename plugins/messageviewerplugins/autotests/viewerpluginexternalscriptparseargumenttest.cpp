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

#include "viewerpluginexternalscriptparseargumenttest.h"
#include "../externalscriptplugin/viewerpluginexternalscriptparseargument.h"
#include <QTest>

ViewerPluginExternalScriptParseArgumentTest::ViewerPluginExternalScriptParseArgumentTest(QObject *parent)
    : QObject(parent)
{

}

ViewerPluginExternalScriptParseArgumentTest::~ViewerPluginExternalScriptParseArgumentTest()
{

}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnOriginalStringListWhenMessageIsNotSetting()
{
    ViewerPluginExternalScriptParseArgument parser;
    const QStringList lst = { QStringLiteral("foo"), QStringLiteral("bla") };
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%s") };
    const QStringList result = { QStringLiteral("\"Akademy\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSameListIfNotTransform()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("cc"),  QStringLiteral("vv"), QStringLiteral("ff")};
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTwiceSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%s"),  QStringLiteral("vv"), QStringLiteral("%s")};
    const QStringList result = { QStringLiteral("\"Akademy\""),  QStringLiteral("vv"), QStringLiteral("\"Akademy\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTo()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%to") };
    const QStringList result = { QStringLiteral("\"kde@example.com\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnEmptyStrWhenArgumentIsNotDefined()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%cc") };
    const QStringList result = { QStringLiteral("\"\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBody()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%body") };
    const QStringList result = { QStringLiteral("\"Hello this is a test mail\n\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBcc()
{
    ViewerPluginExternalScriptParseArgument parser;
    KMime::Message::Ptr message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = { QStringLiteral("%bcc") };
    const QStringList result = { QStringLiteral("\"kde1@example.com\"") };
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::initializeMessage(const KMime::Message::Ptr &msg)
{
    QByteArray mail = "From: dfaure@example.com\n"
                      "To: kde@example.com\n"
                      "Bcc: kde1@example.com\n"
                      "Sender: dfaure@example.com\n"
                      "MIME-Version: 1.0\n"
                      "Date: 02 Jul 2010 23:58:21 -0000\n"
                      "Subject: Akademy\n"
                      "Content-Type: text/plain\n"
                      "X-Length: 0\n"
                      "X-UID: 6161\n"
                      "\n"
                      "Hello this is a test mail\n";
    msg->setContent(mail);
    msg->parse();
}

QTEST_MAIN(ViewerPluginExternalScriptParseArgumentTest)
