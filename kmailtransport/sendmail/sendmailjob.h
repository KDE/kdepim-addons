/*
    Copyright (c) 2007 Volker Krause <vkrause@kde.org>
    Copyright (c) 2007 KovoKs <kovoks@kovoks.nl>

    Based on KMail code by:
    Copyright (c) 1996-1998 Stefan Taferner <taferner@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef MAILTRANSPORT_SENDMAILJOB_H
#define MAILTRANSPORT_SENDMAILJOB_H

#include <mailtransport/transportjob.h>

#include <QtCore/QProcess>

namespace MailTransport {
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
    virtual ~SendmailJob();

protected:
    virtual void doStart();
    virtual bool doKill();

private Q_SLOTS:
    void sendmailExited(int, QProcess::ExitStatus);
    void receivedError();
    void receivedStdErr();

private:
    QString mLastError;
    QProcess *mProcess = nullptr;
};
} // namespace MailTransport

#endif // MAILTRANSPORT_SENDMAILJOB_H
