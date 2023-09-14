/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblocklistsmanager.h"

#include <QDir>
#include <QStandardPaths>

AdblockListsManager::AdblockListsManager(QObject *parent)
    : QObject{parent}
    , mFilterListsPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/filterlists/"))
{
    QDir().mkdir(mFilterListsPath);
}

AdblockListsManager::~AdblockListsManager() = default;

QString AdblockListsManager::filterListsPath() const
{
    return mFilterListsPath;
}

#include "moc_adblocklistsmanager.cpp"
