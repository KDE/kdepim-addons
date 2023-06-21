/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2007 KovoKs <kovoks@kovoks.nl>

    Based on KMail code by:
    SPDX-FileCopyrightText: 1996-1998 Stefan Taferner <taferner@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sendmailjob.h"
#include "sendmailplugin_debug.h"
#include <MailTransport/Transport>

#include <KLocalizedString>
#include <KShell>
#include <QBuffer>

using namespace MailTransport;

SendmailJob::SendmailJob(Transport *transport, QObject *parent)
    : TransportJob(transport, parent)
    , mProcess(new QProcess(this))
{
    connect(mProcess, &QProcess::finished, this, &SendmailJob::sendmailExited);
    connect(mProcess, &QProcess::errorOccurred, this, &SendmailJob::receivedError);
    connect(mProcess, &QProcess::readyReadStandardError, this, &SendmailJob::receivedStdErr);
}

SendmailJob::~SendmailJob() = default;

void SendmailJob::doStart()
{
    QStringList arguments = QStringList() << QStringLiteral("-i") << QStringLiteral("-f") << sender() << to() << cc() << bcc();
    if (!transport()->options().isEmpty()) {
        const QStringList arg = KShell::splitArgs(transport()->options().trimmed());
        arguments << arg;
    }
    qCDebug(MAILTRANSPORT_PLUGIN_LOG) << "Sendmail arguments " << arguments;
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
    return true;
}

#include "moc_sendmailjob.cpp"
