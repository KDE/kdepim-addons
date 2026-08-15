/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresscheckjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../confirmaddresscheckjob.h"
#include <QTest>

ConfirmAddressCheckJobTest::ConfirmAddressCheckJobTest(QObject *parent)
    : QObject(parent)
{
}

ConfirmAddressCheckJobTest::~ConfirmAddressCheckJobTest() = default;

void ConfirmAddressCheckJobTest::shouldHaveEmptyResultByDefault()
{
    ConfirmAddressCheckJob job;
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());
}

void ConfirmAddressCheckJobTest::shouldReturnEmptyResultWhenNoAddress()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.com"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());

    job.setCheckSettings(domains, whiteList, true);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());
}

void ConfirmAddressCheckJobTest::shouldReturnAllValidEmailsDomain()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.com"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@foo.com"_s, u"blabla@foo.com"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.validEmails(), emails);
}

void ConfirmAddressCheckJobTest::shouldReturnAllValidEmailsDomainRejectedDomain()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.com"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@foo.com"_s, u"blabla@foo.com"_s};
    job.setCheckSettings(domains, whiteList, true);
    job.setAddressList(emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), emails);
    QVERIFY(job.validEmails().isEmpty());
}

void ConfirmAddressCheckJobTest::shouldReturnAllInValidEmailsDomain()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.fr"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@foo.com"_s, u"blabla@foo.com"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), emails);
}

void ConfirmAddressCheckJobTest::shouldReturnAllInValidEmailsDomainReject()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.fr"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@foo.com"_s, u"blabla@foo.com"_s};
    job.setCheckSettings(domains, whiteList, true);
    job.setAddressList(emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.validEmails(), emails);
}

void ConfirmAddressCheckJobTest::shouldReturnValidAndInvalid()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.fr"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@bla.com"_s, u"blabla@foo.com"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), QStringList() << u"blabla@foo.com"_s);
    QCOMPARE(job.validEmails(), QStringList() << u"toto@bla.com"_s);
}

void ConfirmAddressCheckJobTest::shouldNotDuplicateValue()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.com"_s, u"bla.com"_s};
    const QStringList whiteList{u"foo@kde.org"_s, u"bla@kde.org"_s};
    const QStringList emails{u"toto@foo.com"_s, u"blabla@foo.com"_s, u"bla <user@foo.com>"_s};
    // The job reports bare addresses, so the mailbox with a display name is reduced to its address.
    const QStringList expected{u"toto@foo.com"_s, u"blabla@foo.com"_s, u"user@foo.com"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(QStringList() << emails << emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QCOMPARE(job.validEmails(), expected);

    job.setCheckSettings(domains, whiteList, true);
    job.setAddressList(QStringList() << emails << emails);
    job.start();
    QVERIFY(job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), expected);
}

void ConfirmAddressCheckJobTest::shouldNotMatchDomainInLocalPart()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{u"foo.com"_s};
    const QStringList whiteList;
    const QStringList emails{u"foo.com@example.org"_s, u"user@foo.com"_s, u"bla <user@foo.com>"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();

    QCOMPARE(job.validEmails(), QStringList() << u"user@foo.com"_s);
    QCOMPARE(job.invalidEmails(), QStringList() << u"foo.com@example.org"_s);
}

void ConfirmAddressCheckJobTest::shouldMatchWhitelistCaseInsensitiveButExact()
{
    ConfirmAddressCheckJob job;
    const QStringList domains;
    const QStringList whiteList{u"Foo@Kde.org"_s};
    const QStringList emails{u"foo@kde.org"_s, u"prefixfoo@kde.org.bad"_s};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();

    QCOMPARE(job.validEmails(), QStringList() << u"foo@kde.org"_s);
    QCOMPARE(job.invalidEmails(), QStringList() << u"prefixfoo@kde.org.bad"_s);
}

void ConfirmAddressCheckJobTest::shouldMatchMailboxWithDisplayName()
{
    // The composer passes full mailboxes, so the domain must be looked up in the address, not in the whole string.
    const QStringList emails{u"Foo Bar <user@foo.com>"_s, u"\"Bar, Foo\" <user@other.com>"_s};

    ConfirmAddressCheckJob acceptedJob;
    acceptedJob.setCheckSettings({u"foo.com"_s}, {}, false);
    acceptedJob.setAddressList(emails);
    acceptedJob.start();
    QCOMPARE(acceptedJob.validEmails(), QStringList() << u"user@foo.com"_s);
    QCOMPARE(acceptedJob.invalidEmails(), QStringList() << u"user@other.com"_s);

    ConfirmAddressCheckJob rejectedJob;
    rejectedJob.setCheckSettings({u"foo.com"_s}, {}, true);
    rejectedJob.setAddressList(emails);
    rejectedJob.start();
    QCOMPARE(rejectedJob.validEmails(), QStringList() << u"user@other.com"_s);
    QCOMPARE(rejectedJob.invalidEmails(), QStringList() << u"user@foo.com"_s);

    // A whitelist entry stores a bare address, it must still match a mailbox with a display name.
    ConfirmAddressCheckJob whiteListJob;
    whiteListJob.setCheckSettings({u"foo.com"_s}, {u"user@other.com"_s}, false);
    whiteListJob.setAddressList(emails);
    whiteListJob.start();
    QCOMPARE(whiteListJob.validEmails(), QStringList() << u"user@foo.com"_s << u"user@other.com"_s);
    QVERIFY(whiteListJob.invalidEmails().isEmpty());
}

QTEST_MAIN(ConfirmAddressCheckJobTest)

#include "moc_confirmaddresscheckjobtest.cpp"
