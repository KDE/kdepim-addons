/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolsjob.h"

#include "akonadidatasetools_debug.h"
#include <QProcess>
#include <QStandardPaths>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
AkonadiDatabaseToolsJob::AkonadiDatabaseToolsJob(QObject *parent)
    : QObject{parent}
{
}

AkonadiDatabaseToolsJob::~AkonadiDatabaseToolsJob() = default;

bool AkonadiDatabaseToolsJob::canStart() const
{
    return !akonadiProcessPath().isEmpty() && (mTool != AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown);
}

QString AkonadiDatabaseToolsJob::akonadiProcessPath() const
{
    const QString exec = TextAddonsWidgets::ExecutableUtils::findExecutable(u"akonadictl"_s);

    return exec;
}

void AkonadiDatabaseToolsJob::setTool(AkonadiDatabaseToolsUtils::AkonadiDatabaseTool newTool)
{
    mTool = newTool;
}

void AkonadiDatabaseToolsJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    switch (mTool) {
    case AkonadiDatabaseToolsUtils::Unknown:
        qCWarning(AKONADIDATABASETOOLS_LOG) << "mTool is unknown it's a bug! ";
        break;
    case AkonadiDatabaseToolsUtils::Vacuum: {
        mProcess = new QProcess(this);
        mProcess->setProgram(akonadiProcessPath());
        mProcess->setArguments(QStringList() << u"vacuum"_s);
        connect(mProcess, &QProcess::finished, this, [this]() {
            Q_EMIT finished();
            deleteLater();
        });
        connect(mProcess, &QProcess::readyReadStandardError, this, [this]() {
            Q_EMIT receivedStandardError(QLatin1StringView(mProcess->readAllStandardError()));
        });
        connect(mProcess, &QProcess::readyReadStandardOutput, this, [this]() {
            Q_EMIT receivedStandardOutput(QLatin1StringView(mProcess->readAllStandardOutput()));
        });
        mProcess->start();
        break;
    }
    case AkonadiDatabaseToolsUtils::Fsck: {
        mProcess = new QProcess(this);
        mProcess->setProgram(akonadiProcessPath());
        mProcess->setArguments(QStringList() << u"fsck"_s);
        connect(mProcess, &QProcess::finished, this, [this]() {
            Q_EMIT finished();
            deleteLater();
        });
        connect(mProcess, &QProcess::readyReadStandardError, this, [this]() {
            Q_EMIT receivedStandardError(QLatin1StringView(mProcess->readAllStandardError()));
        });
        connect(mProcess, &QProcess::readyReadStandardOutput, this, [this]() {
            Q_EMIT receivedStandardOutput(QLatin1StringView(mProcess->readAllStandardOutput()));
        });
        mProcess->start();
        break;
    }
    }
}

#include "moc_akonadidatabasetoolsjob.cpp"
