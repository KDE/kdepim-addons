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

#include "sendmailjob.h"
#include "transport.h"

#include <KLocalizedString>

#include <QProcess>
#include <QBuffer>

using namespace MailTransport;

/**
 * Private class that helps to provide binary compatibility between releases.
 * @internal
 */
class SendMailJobPrivate
{
public:
    QProcess *process = nullptr;
    QString lastError;
};

SendmailJob::SendmailJob(Transport *transport, QObject *parent)
    : TransportJob(transport, parent)
    , d(new SendMailJobPrivate)
{
    d->process = new QProcess(this);
    connect(d->process,
            SIGNAL(finished(int,QProcess::ExitStatus)),
            SLOT(sendmailExited(int,QProcess::ExitStatus)));
    connect(d->process, SIGNAL(error(QProcess::ProcessError)),
            SLOT(receivedError()));
    connect(d->process, SIGNAL(readyReadStandardError()),
            SLOT(receivedStdErr()));
}

SendmailJob::~SendmailJob()
{
    delete d;
}

void SendmailJob::doStart()
{
    const QStringList arguments = QStringList() << QLatin1String("-i") << QLatin1String("-f") << sender() << to() << cc() << bcc();
    d->process->start(transport()->host(), arguments);

    if (!d->process->waitForStarted()) {
        setError(UserDefinedError);
        setErrorText(i18n("Failed to execute mailer program %1", transport()->host()));
        emitResult();
    } else {
        d->process->write(buffer()->readAll());
        d->process->closeWriteChannel();
    }
}

void SendmailJob::sendmailExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != 0 || exitCode != 0) {
        setError(UserDefinedError);
        if (d->lastError.isEmpty()) {
            setErrorText(i18n("Sendmail exited abnormally."));
        } else {
            setErrorText(i18n("Sendmail exited abnormally: %1", d->lastError));
        }
    }
    emitResult();
}

void SendmailJob::receivedError()
{
    d->lastError += d->process->errorString();
}

void SendmailJob::receivedStdErr()
{
    d->lastError += QLatin1String(d->process->readAllStandardError());
}

bool SendmailJob::doKill()
{
    delete d->process;
    d->process = nullptr;
    return true;
}
