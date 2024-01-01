/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
