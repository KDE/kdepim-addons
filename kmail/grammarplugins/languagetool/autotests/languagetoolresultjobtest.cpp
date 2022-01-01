/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultjobtest.h"
#include "languagetoolresultjob.h"
#include <QTest>
QTEST_MAIN(LanguageToolResultJobTest)
LanguageToolResultJobTest::LanguageToolResultJobTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolResultJobTest::shouldHaveDefaultValue()
{
    LanguageToolResultJob job;
    QVERIFY(!job.networkAccessManager());
    QVERIFY(job.arguments().isEmpty());
    QVERIFY(!job.canStart());
    QVERIFY(job.text().isEmpty());
    QVERIFY(job.url().isEmpty());
    QVERIFY(job.language().isEmpty());
}

void LanguageToolResultJobTest::shouldBeAbleToStart()
{
    LanguageToolResultJob job;
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral("foo"));
    QVERIFY(!job.canStart());
    job.setUrl(QStringLiteral("http://www.kde.org"));
    QVERIFY(!job.canStart());
    job.setLanguage(QStringLiteral("foo"));
    QVERIFY(!job.canStart());
    QNetworkAccessManager network;
    job.setNetworkAccessManager(&network);
    QVERIFY(job.canStart());
    job.setText(QStringLiteral(" "));
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral(" DDDD"));
    QVERIFY(job.canStart());
}
