/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailsenderjobtest.h"
#include "mailsenderjob.h"

#include <KContacts/Addressee>

#include <QSignalSpy>
#include <QTest>

MailSenderJobTest::MailSenderJobTest() = default;

void MailSenderJobTest::shouldNotSendSignalWhenWeDontSelectItem()
{
    Akonadi::Item::List lst;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 0);
}

void MailSenderJobTest::shouldNotSendSignalWhenNoValidAddressItem()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    lst << item;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 0);
}

void MailSenderJobTest::shouldNotSendSignalWhenNoEmails()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<KContacts::Addressee>(address);
    lst << item;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 0);
}

void MailSenderJobTest::shouldSendSignalWhenOneEmail()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    KContacts::Email email(QStringLiteral("foo@kde.org"));
    email.setPreferred(true);
    address.addEmail(email);
    item.setPayload<KContacts::Addressee>(address);
    lst << item;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 1);
    const QStringList resultLst = spy.at(0).at(0).toStringList();
    QCOMPARE(resultLst.count(), 1);
}

void MailSenderJobTest::shouldNotSendTwiceEmails()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    KContacts::Email email(QStringLiteral("foo@kde.org"));
    email.setPreferred(true);
    address.addEmail(email);
    item.setPayload<KContacts::Addressee>(address);
    lst << item << item;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    const QStringList resultLst = spy.at(0).at(0).toStringList();
    QCOMPARE(resultLst.count(), 1);
}

void MailSenderJobTest::shouldNotAddInvalidEmail()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    // Invalid email
    KContacts::Email email(QStringLiteral("foo2"));
    email.setPreferred(true);
    address.addEmail(email);
    item.setPayload<KContacts::Addressee>(address);
    lst << item;
    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 0);
}

void MailSenderJobTest::shouldEmitSignalIfThereIsAValidEmail()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    // Invalid email
    KContacts::Email email(QStringLiteral("foo2"));
    email.setPreferred(true);
    address.addEmail(email);
    item.setPayload<KContacts::Addressee>(address);
    lst << item;

    Akonadi::Item item2;
    KContacts::Addressee address2;
    address2.setName(QStringLiteral("foo2"));
    KContacts::Email email2(QStringLiteral("foo2@kde.org"));
    email2.setPreferred(true);
    address2.addEmail(email);
    item2.setPayload<KContacts::Addressee>(address2);
    lst << item2;

    Akonadi::Item item3;
    KContacts::Addressee address3;
    address3.setName(QStringLiteral("foo3"));
    KContacts::Email email3(QStringLiteral("foo3@"));
    email3.setPreferred(true);
    address3.addEmail(email);
    item3.setPayload<KContacts::Addressee>(address3);
    lst << item3;

    Akonadi::Item item4;
    KContacts::Addressee address4;
    address4.setName(QStringLiteral("foo4"));
    KContacts::Email email4(QStringLiteral("foo4@kde.org"));
    email4.setPreferred(true);
    address4.addEmail(email);
    item4.setPayload<KContacts::Addressee>(address4);
    lst << item4;

    KABMailSender::MailSenderJob mailsender(lst);
    QSignalSpy spy(&mailsender, &KABMailSender::MailSenderJob::sendMails);
    mailsender.start();
    QCOMPARE(spy.count(), 1);
    const QStringList resultLst = spy.at(0).at(0).toStringList();
    QCOMPARE(resultLst.count(), 2);
}

// TODO Create unittest for ContactGroup too

QTEST_MAIN(MailSenderJobTest)

#include "moc_mailsenderjobtest.cpp"
