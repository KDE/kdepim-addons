/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkattachmentjobtest.h"
using namespace Qt::Literals::StringLiterals;

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
    QStringList emails{u"foo@kde.org"_s, u"bla@kde.org"_s};
    QStringList createdList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    QTest::newRow("nonempty") << emails << createdList;
    emails = QStringList{u"\"bla\" <foo@kde.org>"_s, u"bla@kde.org"_s};
    QTest::newRow("potentialerrors") << emails << emails;

    emails = QStringList{u"\"bla, foo\" <foo@kde.org>"_s, u"bla@kde.org"_s};
    QTest::newRow("emailswithquote") << emails << emails;

    emails = QStringList{u"\"bla, foo\" <foo@kde.org>"_s, u"bla@kde.org"_s, QStringLiteral(" ")};
    createdList = QStringList{u"\"bla, foo\" <foo@kde.org>"_s, u"bla@kde.org"_s};
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

    QStringList lst{u"foo@kde.org"_s, u"bla@kde.org"_s};
    QTest::newRow("samelist") << lst << lst;

    QStringList original{u"foo@kde.org"_s, u"bla@kde.org"_s, QStringLiteral("bla@kde.org")};
    QStringList result{u"foo@kde.org"_s, u"bla@kde.org"_s};
    QTest::newRow("oneduplicate") << original << result;

    original = QStringList() << u"lolo <foo@kde.org>"_s << u"lulu <bla@kde.org>"_s << QStringLiteral("bla <bla@kde.org>");
    QTest::newRow("oneduplicatewithname") << original << result;

    original = QStringList() << u"lolo <foo@kde.org>"_s << u"lulu <bla@kde.org>"_s << QStringLiteral("bla <bla@kde.org>") << u"bla"_s;
    QTest::newRow("withinvalidemail") << original << result;
}

QTEST_MAIN(CheckAttachmentJobTest)

#include "moc_checkattachmentjobtest.cpp"
