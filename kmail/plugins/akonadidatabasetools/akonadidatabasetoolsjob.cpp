/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolsjob.h"
#include "akonadidatasetools_debug.h"
#include <QProcess>
#include <QStandardPaths>

AkonadiDatabaseToolsJob::AkonadiDatabaseToolsJob(QObject *parent)
    : QObject{parent}
{
}

AkonadiDatabaseToolsJob::~AkonadiDatabaseToolsJob() = default;

bool AkonadiDatabaseToolsJob::canStart() const
{
    return processExist().isEmpty() && (mTool != AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown);
}

QString AkonadiDatabaseToolsJob::processExist() const
{
    return QStandardPaths::findExecutable(QStringLiteral("akonadictl"));
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
    case AkonadiDatabaseToolsUtils::Vaccum: {
        QProcess::execute(QStandardPaths::findExecutable(QStringLiteral("akonadictl")), QStringList({QStringLiteral("vacuum")}));
        break;
    }
    case AkonadiDatabaseToolsUtils::Fsck: {
        QProcess::execute(QStandardPaths::findExecutable(QStringLiteral("akonadictl")), QStringList({QStringLiteral("fsck")}));
        break;
    }
    }

    deleteLater();
}
