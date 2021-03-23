/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2007 KovoKs <kovoks@kovoks.nl>

    Based on KMail code by:
    SPDX-FileCopyrightText: 1996-1998 Stefan Taferner <taferner@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MailTransport/TransportJob>

#include <QProcess>

namespace MailTransport
{
/**
  Mail transport job for sendmail.

  @deprecated Use MessageQueueJob for sending e-mail.
*/
class SendmailJob : public TransportJob
{
    Q_OBJECT
public:
    /**
      Creates a SendmailJob.
      @param transport The transport settings.
      @param parent The parent object.
    */
    explicit SendmailJob(Transport *transport, QObject *parent = nullptr);

    /**
      Destroys this job.
    */
    ~SendmailJob() override;

protected:
    void doStart() override;
    bool doKill() override;

private Q_SLOTS:
    void sendmailExited(int, QProcess::ExitStatus);
    void receivedError();
    void receivedStdErr();

private:
    QString mLastError;
    QProcess *const mProcess;
};
} // namespace MailTransport

