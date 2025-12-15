/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptparseargumenttest.h"
#include "../viewerpluginexternalscriptparseargument.h"
#include <QTest>

ViewerPluginExternalScriptParseArgumentTest::ViewerPluginExternalScriptParseArgumentTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalScriptParseArgumentTest::~ViewerPluginExternalScriptParseArgumentTest() = default;

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnOriginalStringListWhenMessageIsNotSetting()
{
    ViewerPluginExternalScriptParseArgument parser;
    const QStringList lst = {QStringLiteral("foo"), QStringLiteral("bla")};
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%s")};
    const QStringList result = {QStringLiteral("\"Akademy\"")};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnSameListIfNotTransform()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("cc"), QStringLiteral("vv"), QStringLiteral("ff")};
    QCOMPARE(parser.parse(lst), lst);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTwiceSubject()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%s"), QStringLiteral("vv"), QStringLiteral("%s")};
    const QStringList result = {QStringLiteral("\"Akademy\""), QStringLiteral("vv"), QStringLiteral("\"Akademy\"")};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnTo()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%to")};
    const QStringList result = {QStringLiteral("\"kde@example.com\"")};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnEmptyStrWhenArgumentIsNotDefined()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%cc")};
    const QStringList result = {QStringLiteral("\"\"")};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBody()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%body")};
    const QStringList result = {QStringLiteral("\"Hello this is a test mail\n\"")};
    QCOMPARE(parser.parse(lst), result);
}

void ViewerPluginExternalScriptParseArgumentTest::shouldReturnBcc()
{
    ViewerPluginExternalScriptParseArgument parser;
    std::shared_ptr<KMime::Message> message(new KMime::Message);
    initializeMessage(message);
    parser.setMessage(message);
    const QStringList lst = {QStringLiteral("%bcc")};
    const QStringList result = {QStringLiteral("\"kde1@example.com\"")};
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
