/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanager.h"
#include "globalsettings_webengineurlinterceptoradblock.h"

AdblockManager::AdblockManager(QObject *parent)
    : QObject{parent}
{
    reloadConfig();
}

AdblockManager::~AdblockManager() = default;

AdblockManager *AdblockManager::self()
{
    static AdblockManager s_self;
    return &s_self;
}

void AdblockManager::reloadConfig()
{
    // loadSubscriptions();
    const bool enabled = AdBlockSettings::self()->adBlockEnabled();
    Q_EMIT enabledChanged(enabled);
}

#include "moc_adblockmanager.cpp"
