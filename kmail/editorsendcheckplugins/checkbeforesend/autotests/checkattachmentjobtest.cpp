/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "checkattachmentjobtest.h"
#include "../sendattachments/checkattachmentjob.h"

#include <QTest>

CheckAttachmentJobTest::CheckAttachmentJobTest(QObject *parent)
    : QObject(parent)
{
}

CheckAttachmentJobTest::~CheckAttachmentJobTest()
{
}

void CheckAttachmentJobTest::shouldHaveDefaultValue()
{
    CheckAttachmentJob job;
    QVERIFY(job.resultList().isEmpty());
    QVERIFY(job.originalEmails().isEmpty());

    job.start();
    QVERIFY(job.resultList().isEmpty());
    QVERIFY(job.originalEmails().isEmpty());
}

void CheckAttachmentJobTest::shouldAssignEmails_data()
{
    QTest::addColumn<QStringList>("originalEmails");
    QTest::addColumn<QStringList>("result");
    QTest::newRow("emptylist") << QStringList() << QStringList();
    QStringList emails{
        QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")
    };
    QStringList createdList{
        QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("nonempty") << emails << createdList;
    emails = QStringList{
        QStringLiteral("\"bla\" <foo@kde.org>"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("potentialerrors") << emails << emails;

    emails = QStringList{
        QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("emailswithquote") << emails << emails;

    emails = QStringList{
        QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org"), QStringLiteral(" ")
    };
    createdList = QStringList{
        QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("emailswithemptystr") << emails << createdList;
}

void CheckAttachmentJobTest::shouldAssignEmails()
{
    QFETCH(QStringList, originalEmails);
    QFETCH(QStringList, result);

    CheckAttachmentJob job;
    job.setOriginalEmails(originalEmails);
    QCOMPARE(job.originalEmails(), result);
}

void CheckAttachmentJobTest::shouldRemoveDuplicatedEmails()
{
    QFETCH(QStringList, originalEmails);
    QFETCH(QStringList, result);
    CheckAttachmentJob job;
    job.setOriginalEmails(originalEmails);
    job.start();
    QCOMPARE(job.resultList(), result);
}

void CheckAttachmentJobTest::shouldRemoveDuplicatedEmails_data()
{
    QTest::addColumn<QStringList>("originalEmails");
    QTest::addColumn<QStringList>("result");
    QTest::newRow("empty") << QStringList() << QStringList();

    QStringList lst {
        QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("samelist") << lst << lst;

    QStringList original {
        QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org"), QStringLiteral("bla@kde.org")
    };
    QStringList result {
        QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")
    };
    QTest::newRow("oneduplicate") << original << result;

    original = QStringList() << QStringLiteral("lolo <foo@kde.org>") << QStringLiteral("lulu <bla@kde.org>") << QStringLiteral("bla <bla@kde.org>");
    QTest::newRow("oneduplicatewithname") << original << result;

    original = QStringList() << QStringLiteral("lolo <foo@kde.org>") << QStringLiteral("lulu <bla@kde.org>") << QStringLiteral("bla <bla@kde.org>") << QStringLiteral("bla");
    QTest::newRow("withinvalidemail") << original << result;
}

QTEST_MAIN(CheckAttachmentJobTest)
