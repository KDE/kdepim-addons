/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolsjob.h"

AkonadiDatabaseToolsJob::AkonadiDatabaseToolsJob(QObject *parent)
    : QObject{parent}
{
}

AkonadiDatabaseToolsJob::~AkonadiDatabaseToolsJob() = default;

bool AkonadiDatabaseToolsJob::canStart() const
{
    // TODO
    return false;
}

void AkonadiDatabaseToolsJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    // TODO
}
