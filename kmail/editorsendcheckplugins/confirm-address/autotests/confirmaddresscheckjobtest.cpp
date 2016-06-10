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


#include "confirmaddresscheckjobtest.h"
#include "../confirmaddresscheckjob.h"
#include <QTest>

ConfirmAddressCheckJobTest::ConfirmAddressCheckJobTest(QObject *parent)
    : QObject(parent)
{

}

ConfirmAddressCheckJobTest::~ConfirmAddressCheckJobTest()
{

}

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
    job.setCheckSettings(domains, whiteList);
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
    job.setCheckSettings(domains, whiteList);
    job.setAddressList(emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.validEmails(), emails);
}

void ConfirmAddressCheckJobTest::shouldReturnAllInValidEmailsDomain()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{QStringLiteral("foo.fr"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@foo.com"), QStringLiteral("blabla@foo.com")};
    job.setCheckSettings(domains, whiteList);
    job.setAddressList(emails);
    job.start();
    QVERIFY(!job.invalidEmails().isEmpty());
    QVERIFY(job.validEmails().isEmpty());
    QCOMPARE(job.invalidEmails(), emails);
}

void ConfirmAddressCheckJobTest::shouldReturnValidAndInvalid()
{
    ConfirmAddressCheckJob job;
    const QStringList domains{QStringLiteral("foo.fr"), QStringLiteral("bla.com")};
    const QStringList whiteList{QStringLiteral("foo@kde.org"), QStringLiteral("bla@kde.org")};
    const QStringList emails{QStringLiteral("toto@bla.com"), QStringLiteral("blabla@foo.com")};
    job.setCheckSettings(domains, whiteList);
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
    job.setCheckSettings(domains, whiteList);
    job.setAddressList(QStringList() << emails << emails);
    job.start();
    QVERIFY(job.invalidEmails().isEmpty());
    QVERIFY(!job.validEmails().isEmpty());
    QCOMPARE(job.validEmails(), emails);

}

QTEST_MAIN(ConfirmAddressCheckJobTest)
