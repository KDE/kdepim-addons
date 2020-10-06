/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultjob.h"
#include "libgrammalecte_debug.h"

#include <QTemporaryFile>

GrammalecteResultJob::GrammalecteResultJob(QObject *parent)
    : QObject(parent)
{
}

GrammalecteResultJob::~GrammalecteResultJob()
{
}

void GrammalecteResultJob::start()
{
    if (canStart()) {
        mProcess = new QProcess(this);

        QTemporaryFile *file = new QTemporaryFile(this);
        file->open();
        file->setPermissions(QFile::ReadUser);
        file->write(mText.toUtf8());
        file->close();

        mProcess->setProgram(mPythonPath);
        QStringList args;
        args << mGrammarlecteCliPath;
        if (!mArguments.isEmpty()) {
            args << QStringLiteral("-on") << mArguments;
        }
        args << QStringLiteral("-f") << file->fileName() << QStringLiteral("-j");
        mProcess->setArguments(args);
        connect(mProcess, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &GrammalecteResultJob::slotFinished);
        connect(mProcess, qOverload<QProcess::ProcessError>(&QProcess::errorOccurred),
                this, &GrammalecteResultJob::receivedError);
        connect(mProcess, &QProcess::readyReadStandardError, this, &GrammalecteResultJob::receivedStdErr);
        connect(mProcess, &QProcess::readyReadStandardOutput, this, &GrammalecteResultJob::receivedStandardOutput);

        mProcess->start();
        if (!mProcess->waitForStarted()) {
            qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Impossible to start grammarresultjob";
            Q_EMIT error(ErrorType::Unknown);
            deleteLater();
        }
    } else {
        if (mErrorType != ErrorType::TextIsEmpty) {
            Q_EMIT error(mErrorType);
        }
        deleteLater();
    }
}

void GrammalecteResultJob::receivedStandardOutput()
{
    mResult += QString::fromUtf8(mProcess->readAllStandardOutput());
}

void GrammalecteResultJob::receivedError()
{
    mLastError += mProcess->errorString();
}

void GrammalecteResultJob::receivedStdErr()
{
    mLastError += QLatin1String(mProcess->readAllStandardError());
}

void GrammalecteResultJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != 0 || exitCode != 0) {
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Error during running GrammarResultJob: " << mLastError;
    } else {
        Q_EMIT finished(mResult);
    }
    deleteLater();
}

QStringList GrammalecteResultJob::arguments() const
{
    return mArguments;
}

void GrammalecteResultJob::setArguments(const QStringList &arguments)
{
    mArguments = arguments;
}

QString GrammalecteResultJob::grammarlecteCliPath() const
{
    return mGrammarlecteCliPath;
}

void GrammalecteResultJob::setGrammarlecteCliPath(const QString &grammarlecteCliPath)
{
    mGrammarlecteCliPath = grammarlecteCliPath;
}

QString GrammalecteResultJob::pythonPath() const
{
    return mPythonPath;
}

void GrammalecteResultJob::setPythonPath(const QString &pythonPath)
{
    mPythonPath = pythonPath;
}

static bool hasNotEmptyText(const QString &text)
{
    for (int i = 0; i < text.length(); ++i) {
        if (!text.at(i).isSpace()) {
            return true;
        }
    }
    return false;
}

bool GrammalecteResultJob::canStart()
{
    if (!hasNotEmptyText(mText)) {
        mErrorType = ErrorType::TextIsEmpty;
        return false;
    }
    if (mGrammarlecteCliPath.isEmpty()) {
        mErrorType = ErrorType::GrammalecteMissing;
        return false;
    }
    if (mPythonPath.isEmpty()) {
        mErrorType = ErrorType::PythonPathMissing;
        return false;
    }
    return true;
}

QString GrammalecteResultJob::text() const
{
    return mText;
}

void GrammalecteResultJob::setText(const QString &text)
{
    mText = text;
}
