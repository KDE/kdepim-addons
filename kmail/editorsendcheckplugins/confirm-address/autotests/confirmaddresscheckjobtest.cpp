/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresscheckjobtest.h"
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
    const QStringList domains{QStringLiteral("foo.com"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
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
    const QStringList domains{QStringLiteral("foo.com"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
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
    const QStringList domains{QStringLiteral("foo.com"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
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
    const QStringList domains{QStringLiteral("foo.fr"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
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
    const QStringList domains{QStringLiteral("foo.fr"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
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
    const QStringList domains{QStringLiteral("foo.fr"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@bla.com"), QStringLiteral("blabla@foo.com")};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), QStringList() << QStringLiteral("blabla@foo.com"));
    QCOMPARE(job.validEmails(), QStringList() << QStringLiteral("toto@bla.com"));
}

void ConfirmAddressCheckJobTest::shouldNotDuplicateValue()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{QStringLiteral("foo.com"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
    job.setCheckSettings(domains, whiteList, false);
    job.setAddressList(QStringList() << emails << emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.validEmails(), emails);

    job.setCheckSettings(domains, whiteList, true);
    job.setAddressList(QStringList() << emails << emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), emails);
}

QTEST_MAIN(ConfirmAddressCheckJobTest)

#include "moc_confirmaddresscheckjobtest.cpp"
