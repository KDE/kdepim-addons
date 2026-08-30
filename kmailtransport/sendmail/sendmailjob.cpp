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
using namespace Qt::Literals::StringLiterals;

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
    QStringList arguments;
    if (!transport()->options().isEmpty()) {
        KShell::Errors err = KShell::NoError;
        const QStringList options = KShell::splitArgs(transport()->options().trimmed(), KShell::NoOptions, &err);
        if (err != KShell::NoError) {
            setError(UserDefinedError);
            setErrorText(i18n("Invalid options for the mailer program: %1", transport()->options()));
            emitResult();
            return;
        }
        arguments << options;
    }
    // "--" makes sure that a recipient starting with '-' is not treated as an option.
    arguments << u"-i"_s << u"-f"_s << sender() << u"--"_s << to() << cc() << bcc();
    qCDebug(MAILTRANSPORT_PLUGIN_LOG) << "Sendmail arguments " << arguments;
    mProcess->start(transport()->host(), arguments);

    if (!mProcess->waitForStarted()) {
        // No slot must be called after we emitted the result, and the process might
        // have been started but timed out, so make sure it does not outlive us.
        mProcess->disconnect(this);
        mProcess->kill();
        setError(UserDefinedError);
        if (mLastError.isEmpty()) {
            setErrorText(i18n("Failed to execute mailer program %1", transport()->host()));
        } else {
            setErrorText(i18n("Failed to execute mailer program %1: %2", transport()->host(), mLastError));
        }
        emitResult();
    } else {
        mProcess->write(buffer()->readAll());
        mProcess->closeWriteChannel();
    }
}

void SendmailJob::sendmailExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
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
    mLastError += QString::fromUtf8(mProcess->readAllStandardError());
}

bool SendmailJob::doKill()
{
    // Do not delete the process here: ~QProcess() kills and waits for a still running
    // process, which emits finished() and would re-enter emitResult() from within
    // KJob::kill(). The process is a child of this job, so it is reaped anyway.
    mProcess->disconnect(this);
    mProcess->terminate();
    return true;
}

#include "moc_sendmailjob.cpp"
