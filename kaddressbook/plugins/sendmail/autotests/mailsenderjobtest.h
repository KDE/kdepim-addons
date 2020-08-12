/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILSENDERJOBTEST_H
#define MAILSENDERJOBTEST_H

#include <QObject>

class MailSenderJobTest : public QObject
{
    Q_OBJECT
public:
    MailSenderJobTest();

private Q_SLOTS:
    void shouldNotSendSignalWhenWeDontSelectItem();
    void shouldNotSendSignalWhenNoValidAddressItem();
    void shouldNotSendSignalWhenNoEmails();
    void shouldSendSignalWhenOneEmail();
    void shouldNotSendTwiceEmails();
    void shouldNotAddInvalidEmail();
    void shouldEmitSignalIfThereIsAValidEmail();
};

#endif // MAILSENDERJOBTEST_H
