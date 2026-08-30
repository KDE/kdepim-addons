/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptparseargumenttest.h"
#include "../viewerpluginexternalscriptparseargument.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalScriptParseArgumentTest::ViewerPluginExternalScriptParseArgumentTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalScriptParseArgumentTest::~ViewerPluginExternalScriptParseArgumentTest() = default;

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnOriginalStringListWhenMessageIsNotSetting()
{
    ViewerPluginExternalScriptParseArgument parser;
    const QStringList lst = {u"foo"_s, u"bla"_s};
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%s"_s};
    const QStringList result = {u"\"Akademy\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSameListIfNotTransform()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"cc"_s, u"vv"_s, u"ff"_s};
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTwiceSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%s"_s, u"vv"_s, u"%s"_s};
    const QStringList result = {u"\"Akademy\""_s, u"vv"_s, u"\"Akademy\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTo()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%to"_s};
    const QStringList result = {u"\"kde@example.com\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnEmptyStrWhenArgumentIsNotDefined()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%cc"_s};
    const QStringList result = {u"\"\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBody()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%body"_s};
    const QStringList result = {u"\"Hello this is a test mail\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBcc()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {u"%bcc"_s};
    const QStringList result = {u"\"kde1@example.com\""_s};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::initializeMessage(const std::shared_ptr<KMime::Message> &msg)
{
    QByteArray mail =
        "From: dfaure@example.com\n"
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

#include "moc_viewerpluginexternalscriptparseargumenttest.cpp"
