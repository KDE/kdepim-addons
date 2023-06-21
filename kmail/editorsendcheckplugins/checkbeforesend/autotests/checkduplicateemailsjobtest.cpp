/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsjobtest.h"
#include "../duplicateemails/checkduplicateemailsjob.h"
#include <QStringList>
#include <QTest>

CheckDuplicateEmailsJobTest::CheckDuplicateEmailsJobTest(QObject *parent)
    : QObject(parent)
{
}

CheckDuplicateEmailsJobTest::~CheckDuplicateEmailsJobTest() = default;

void CheckDuplicateEmailsJobTest::shouldHaveDefaultValue()
{
    CheckDuplicateEmailsJob job;
    QVERIFY(job.result().isEmpty());
}

void CheckDuplicateEmailsJobTest::shouldReturnEmptyListWhenEmailsListIsEmpty()
{
    CheckDuplicateEmailsJob job;
    QStringList listEmails;
    job.setEmails(listEmails);
    job.start();
    QVERIFY(job.result().isEmpty());
}

void CheckDuplicateEmailsJobTest::shouldReturnEmails_data()
{
    QTest::addColumn<QStringList>("emails");
    QTest::addColumn<QMap<QString, int>>("result");
    QTest::newRow("empty") << QStringList() << QMap<QString, int>();

    QStringList lst;
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("bla@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    QTest::newRow("emptyresultbutnotemptylist") << lst << QMap<QString, int>();

    lst.clear();
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    QMap<QString, int> result;
    result.insert(QStringLiteral("foo@kde.org"), 2);
    QTest::newRow("oneduplicateemails") << lst << result;

    lst.clear();
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    result.clear();
    result.insert(QStringLiteral("foo@kde.org"), 2);
    result.insert(QStringLiteral("blo@kde.org"), 2);
    QTest::newRow("twoduplicateemails") << lst << result;

    lst.clear();
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    result.clear();
    result.insert(QStringLiteral("foo@kde.org"), 3);
    result.insert(QStringLiteral("blo@kde.org"), 2);
    QTest::newRow("twoduplicateemailswithdifferentvalue") << lst << result;

    lst.clear();
    lst.append(QStringLiteral("foo <foo@kde.org>"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));
    lst.append(QStringLiteral("blo@kde.org"));

    result.clear();
    result.insert(QStringLiteral("foo@kde.org"), 3);
    result.insert(QStringLiteral("blo@kde.org"), 2);
    QTest::newRow("twoduplicateemailswithemailname") << lst << result;

    lst.clear();
    lst.append(QStringLiteral("foo <foo@kde.org>, foo@kde.org, foo@kde.org"));
    lst.append(QStringLiteral("foo@kde.org"));

    result.clear();
    result.insert(QStringLiteral("foo@kde.org"), 4);
    QTest::newRow("emailseparatedbycommat") << lst << result;
}

void CheckDuplicateEmailsJobTest::shouldReturnEmails()
{
    QFETCH(QStringList, emails);
    using mapEmails = QMap<QString, int>;
    QFETCH(mapEmails, result);
    CheckDuplicateEmailsJob job;
    job.setEmails(emails);
    job.start();
    QCOMPARE(job.result(), result);
}

QTEST_MAIN(CheckDuplicateEmailsJobTest)

#include "moc_checkduplicateemailsjobtest.cpp"
