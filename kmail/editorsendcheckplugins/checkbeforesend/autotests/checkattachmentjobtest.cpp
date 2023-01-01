/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkattachmentjobtest.h"
#include "../sendattachments/checkattachmentjob.h"

#include <QTest>

CheckAttachmentJobTest::CheckAttachmentJobTest(QObject *parent)
    : QObject(parent)
{
}

CheckAttachmentJobTest::~CheckAttachmentJobTest() = default;

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
    QStringList emails{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    QStringList createdList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    QTest::newRow("nonempty") << emails << createdList;
    emails = QStringList{QStringLiteral("\"bla\" <foo@kde.org>"), QStringLiteral("bla@kde.org")};
    QTest::newRow("potentialerrors") << emails << emails;

    emails = QStringList{QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org")};
    QTest::newRow("emailswithquote") << emails << emails;

    emails = QStringList{QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org"), QStringLiteral(" ")};
    createdList = QStringList{QStringLiteral("\"bla, foo\" <foo@kde.org>"), QStringLiteral("bla@kde.org")};
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

    QStringList lst{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    QTest::newRow("samelist") << lst << lst;

    QStringList original{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org"), QStringLiteral("bla@kde.org")};
    QStringList result{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    QTest::newRow("oneduplicate") << original << result;

    original = QStringList() << QStringLiteral("lolo <foo@kde.org>") << QStringLiteral("lulu <bla@kde.org>") << QStringLiteral("bla <bla@kde.org>");
    QTest::newRow("oneduplicatewithname") << original << result;

    original = QStringList() << QStringLiteral("lolo <foo@kde.org>") << QStringLiteral("lulu <bla@kde.org>") << QStringLiteral("bla <bla@kde.org>")
                             << QStringLiteral("bla");
    QTest::newRow("withinvalidemail") << original << result;
}

QTEST_MAIN(CheckAttachmentJobTest)
