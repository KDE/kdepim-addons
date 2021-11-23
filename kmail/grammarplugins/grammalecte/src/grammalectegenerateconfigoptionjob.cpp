/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegenerateconfigoptionjob.h"
#include "libgrammalecte_debug.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

GrammalecteGenerateConfigOptionJob::GrammalecteGenerateConfigOptionJob(QObject *parent)
    : QObject(parent)
{
}

GrammalecteGenerateConfigOptionJob::~GrammalecteGenerateConfigOptionJob() = default;

//^([a-zA-Z0-9]+):\s*(True|False)\s*(.*)$
void GrammalecteGenerateConfigOptionJob::start()
{
    if (canStart()) {
        mProcess = new QProcess(this);
        mProcess->setProgram(mPythonPath);
        mProcess->setArguments(QStringList() << mGrammarlecteCliPath << QStringLiteral("-lo"));
        connect(mProcess, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &GrammalecteGenerateConfigOptionJob::slotFinished);
        connect(mProcess, qOverload<QProcess::ProcessError>(&QProcess::errorOccurred), this, &GrammalecteGenerateConfigOptionJob::receivedError);
        connect(mProcess, &QProcess::readyReadStandardError, this, &GrammalecteGenerateConfigOptionJob::receivedStdErr);
        connect(mProcess, &QProcess::readyReadStandardOutput, this, &GrammalecteGenerateConfigOptionJob::receivedStandardOutput);
        mProcess->start();
        if (!mProcess->waitForStarted()) {
            qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Impossible to start GrammalecteGenerateConfigOptionJob";
            Q_EMIT error();
            deleteLater();
        }
    } else {
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Impossible to start GrammalecteGenerateConfigOptionJob";
        Q_EMIT error();
        deleteLater();
    }
}

bool GrammalecteGenerateConfigOptionJob::canStart() const
{
    if (mPythonPath.isEmpty() || mGrammarlecteCliPath.isEmpty()) {
        return false;
    }
    return true;
}

void GrammalecteGenerateConfigOptionJob::receivedError()
{
    mLastError += mProcess->errorString();
}

void GrammalecteGenerateConfigOptionJob::receivedStdErr()
{
    mLastError += QLatin1String(mProcess->readAllStandardError());
}

QString GrammalecteGenerateConfigOptionJob::pythonPath() const
{
    return mPythonPath;
}

void GrammalecteGenerateConfigOptionJob::setPythonPath(const QString &pythonPath)
{
    mPythonPath = pythonPath;
}

QString GrammalecteGenerateConfigOptionJob::grammarlecteCliPath() const
{
    return mGrammarlecteCliPath;
}

void GrammalecteGenerateConfigOptionJob::setGrammarlecteCliPath(const QString &grammarlecteCliPath)
{
    mGrammarlecteCliPath = grammarlecteCliPath;
}

void GrammalecteGenerateConfigOptionJob::receivedStandardOutput()
{
    mResult += QString::fromUtf8(mProcess->readAllStandardOutput());
}

void GrammalecteGenerateConfigOptionJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != 0 || exitCode != 0) {
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "GrammalecteGenerateConfigOptionJob ERROR: " << mLastError;
        Q_EMIT error();
    } else {
        Q_EMIT finished(parseResult());
    }
    deleteLater();
}

QVector<GrammalecteGenerateConfigOptionJob::Option> GrammalecteGenerateConfigOptionJob::parseResult() const
{
    QVector<GrammalecteGenerateConfigOptionJob::Option> opts;
    static const QRegularExpression reg(QStringLiteral("^([a-zA-Z0-9]+):\\s*(True|False)\\s*(.*)$"));
    const QStringList lst = mResult.split(QLatin1Char('\n'));
    for (const QString &str : lst) {
        const QRegularExpressionMatch match = reg.match(str);
        if (match.hasMatch()) {
            const QString optionName = match.captured(1);
            const QString value = match.captured(2);
            const QString description = match.captured(3);
            if (!optionName.isEmpty() && !description.isEmpty() && !value.isEmpty()) {
                if (description == QLatin1Char('?')) {
                    continue;
                }
                GrammalecteGenerateConfigOptionJob::Option opt;
                opt.description = description;
                opt.optionName = optionName;
                opt.defaultValue = (value == QLatin1String("True"));
                opts.append(opt);
            }
        }
    }
    return opts;
}
