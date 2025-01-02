/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendvcardsjobtest.h"
#include "sendvcards/sendvcardsjob.h"
#include <Akonadi/Item>
#include <QTest>
SendVcardsJobTest::SendVcardsJobTest(QObject *parent)
    : QObject(parent)
{
}

SendVcardsJobTest::~SendVcardsJobTest() = default;

void SendVcardsJobTest::shouldNotStartWhenListAddressIsEmpty()
{
    Akonadi::Item::List lst;
    KABSendVCards::SendVcardsJob job(lst);
    QVERIFY(!job.start());
}

void SendVcardsJobTest::shouldHasDefaultValue()
{
    Akonadi::Item::List lst;
    KABSendVCards::SendVcardsJob job(lst);
    QCOMPARE(job.version(), KContacts::VCardConverter::v3_0);
}

void SendVcardsJobTest::shouldChangeExportVersion()
{
    Akonadi::Item::List lst;
    KABSendVCards::SendVcardsJob job(lst);
    job.setVersion(KContacts::VCardConverter::v4_0);
    QCOMPARE(job.version(), KContacts::VCardConverter::v4_0);
}

QTEST_MAIN(SendVcardsJobTest)

#include "moc_sendvcardsjobtest.cpp"
