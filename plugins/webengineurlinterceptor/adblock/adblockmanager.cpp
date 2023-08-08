/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanager.h"

AdblockManager::AdblockManager(QObject *parent)
    : QObject{parent}
{
}

AdblockManager::~AdblockManager() = default;

AdblockManager *AdblockManager::self()
{
    static AdblockManager s_self;
    return &s_self;
}
