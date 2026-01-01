/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsjobtest.h"
using namespace Qt::Literals::StringLiterals;

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
    lst.append(u"foo@kde.org"_s);
    lst.append(u"bla@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    QTest::newRow("emptyresultbutnotemptylist") << lst << QMap<QString, int>();

    lst.clear();
    lst.append(u"foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    QMap<QString, int> result;
    result.insert(u"foo@kde.org"_s, 2);
    QTest::newRow("oneduplicateemails") << lst << result;

    lst.clear();
    lst.append(u"foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    result.clear();
    result.insert(u"foo@kde.org"_s, 2);
    result.insert(u"blo@kde.org"_s, 2);
    QTest::newRow("twoduplicateemails") << lst << result;

    lst.clear();
    lst.append(u"foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    result.clear();
    result.insert(u"foo@kde.org"_s, 3);
    result.insert(u"blo@kde.org"_s, 2);
    QTest::newRow("twoduplicateemailswithdifferentvalue") << lst << result;

    lst.clear();
    lst.append(u"foo <foo@kde.org>"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);
    lst.append(u"blo@kde.org"_s);

    result.clear();
    result.insert(u"foo@kde.org"_s, 3);
    result.insert(u"blo@kde.org"_s, 2);
    QTest::newRow("twoduplicateemailswithemailname") << lst << result;

    lst.clear();
    lst.append(u"foo <foo@kde.org>, foo@kde.org, foo@kde.org"_s);
    lst.append(u"foo@kde.org"_s);

    result.clear();
    result.insert(u"foo@kde.org"_s, 4);
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
