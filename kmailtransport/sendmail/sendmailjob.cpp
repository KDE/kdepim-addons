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

SendmailJob::SendmailJob(Transport *transport, QObject *parent)
    : TransportJob(transport, parent)
{
    mProcess = new QProcess(this);
    connect(mProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SendmailJob::sendmailExited);
    connect(mProcess, QOverload<QProcess::ProcessError>::of(&QProcess::error),
            this, &SendmailJob::receivedError);
    connect(mProcess, &QProcess::readyReadStandardError, this, &SendmailJob::receivedStdErr);
}

SendmailJob::~SendmailJob()
{
}

void SendmailJob::doStart()
{
    const QStringList arguments = QStringList() << QStringLiteral("-i") << QStringLiteral("-f") << sender() << to() << cc() << bcc();
    mProcess->start(transport()->host(), arguments);

    if (!mProcess->waitForStarted()) {
        setError(UserDefinedError);
        setErrorText(i18n("Failed to execute mailer program %1", transport()->host()));
        emitResult();
    } else {
        mProcess->write(buffer()->readAll());
        mProcess->closeWriteChannel();
    }
}

void SendmailJob::sendmailExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != 0 || exitCode != 0) {
        setError(UserDefinedError);
        if (mLastError.isEmpty()) {
            setErrorText(i18n("Sendmail exited abnormally."));
        } else {
            setErrorText(i18n("Sendmail exited abnormally: %1", mLastError));
        }
    }
    emitResult();
}

void SendmailJob::receivedError()
{
    mLastError += mProcess->errorString();
}

void SendmailJob::receivedStdErr()
{
    mLastError += QLatin1String(mProcess->readAllStandardError());
}

bool SendmailJob::doKill()
{
    delete mProcess;
    mProcess = nullptr;
    return true;
}
