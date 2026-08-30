/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailsenderjobtest.h"
#include "mailsenderjob.h"

#include <KContacts/Addressee>

#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

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
    address.setName(u"foo1"_s);
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
    address.setName(u"foo1"_s);
    KContacts::Email email(u"foo@kde.org"_s);
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
    address.setName(u"foo1"_s);
    KContacts::Email email(u"foo@kde.org"_s);
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
    address.setName(u"foo1"_s);
    // Invalid email
    KContacts::Email email(u"foo2"_s);
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
    address.setName(u"foo1"_s);
    // Invalid email
    KContacts::Email email(u"foo2"_s);
    email.setPreferred(true);
    address.addEmail(email);
    item.setPayload<KContacts::Addressee>(address);
    lst << item;

    Akonadi::Item item2;
    KContacts::Addressee address2;
    address2.setName(u"foo2"_s);
    KContacts::Email email2(u"foo2@kde.org"_s);
    email2.setPreferred(true);
    address2.addEmail(email2);
    item2.setPayload<KContacts::Addressee>(address2);
    lst << item2;

    Akonadi::Item item3;
    KContacts::Addressee address3;
    address3.setName(u"foo3"_s);
    KContacts::Email email3(u"foo3@"_s);
    email3.setPreferred(true);
    address3.addEmail(email3);
    item3.setPayload<KContacts::Addressee>(address3);
    lst << item3;

    Akonadi::Item item4;
    KContacts::Addressee address4;
    address4.setName(u"foo4"_s);
    KContacts::Email email4(u"foo4@kde.org"_s);
    email4.setPreferred(true);
    address4.addEmail(email4);
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
