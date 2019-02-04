/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "grammalectegenerateconfigoptionjob.h"
#include "grammalecteplugin_debug.h"

GrammalecteGenerateConfigOptionJob::GrammalecteGenerateConfigOptionJob(QObject *parent)
    : QObject(parent)
{

}

GrammalecteGenerateConfigOptionJob::~GrammalecteGenerateConfigOptionJob()
{

}
//^([a-zA-Z0-9]+):\s*(True|False)\s*(.*)$
void GrammalecteGenerateConfigOptionJob::start()
{
    if (canStart()) {
        mProcess = new QProcess(this);
        mProcess->setProgram(mPythonPath);
        mProcess->setArguments(QStringList() << mGrammarlecteCliPath << QStringLiteral("-lo"));
        connect(mProcess, QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished), this, &GrammalecteGenerateConfigOptionJob::slotFinished);
//        connect(mProcess, QOverload<QProcess::ProcessError>::of(&QProcess::error),
//                this, &GrammalecteGenerateConfigOptionJob::receivedError);
//        connect(mProcess, &QProcess::readyReadStandardError, this, &GrammalecteGenerateConfigOptionJob::receivedStdErr);
        connect(mProcess, &QProcess::readyReadStandardOutput, this, &GrammalecteGenerateConfigOptionJob::receivedStandardOutput);
        mProcess->start();
        if (!mProcess->waitForStarted()) {
            qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Impossible to start GrammalecteGenerateConfigOptionJob";
            Q_EMIT error();
            deleteLater();
        }
    } else {
        qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Impossible to start GrammalecteGenerateConfigOptionJob";
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
        qDebug() << " ERROR :!!!!!!!!!!!!!!!!!!!!";
    } else {
        //TODO fixit !
        Q_EMIT finished(QStringList() << mResult);
    }
    deleteLater();
}
