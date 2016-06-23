/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "checkduplicateemailsjobtest.h"
#include "../checkduplicateemailsjob.h"
#include <QTest>
#include <QStringList>

CheckDuplicateEmailsJobTest::CheckDuplicateEmailsJobTest(QObject *parent)
    : QObject(parent)
{

}

CheckDuplicateEmailsJobTest::~CheckDuplicateEmailsJobTest()
{

}

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
    QTest::addColumn<QMap<QString, int> >("result");
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

}

void CheckDuplicateEmailsJobTest::shouldReturnEmails()
{
    QFETCH(QStringList, emails);
    typedef QMap<QString, int> mapEmails;
    QFETCH(mapEmails, result);
    CheckDuplicateEmailsJob job;
    job.setEmails(emails);
    job.start();
    QCOMPARE(job.result(), result);
}

QTEST_MAIN(CheckDuplicateEmailsJobTest)
