/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmanager.h"

ConfirmBeforeDeletingManager::ConfirmBeforeDeletingManager(QObject *parent)
    : QObject(parent)
{
}

ConfirmBeforeDeletingManager::~ConfirmBeforeDeletingManager()
{
}

ConfirmBeforeDeletingManager *ConfirmBeforeDeletingManager::self()
{
    static ConfirmBeforeDeletingManager s_self;
    return &s_self;
}

void ConfirmBeforeDeletingManager::loadRules()
{
    // TODO
}

void ConfirmBeforeDeletingManager::saveRules()
{
    // TODO
}

bool ConfirmBeforeDeletingManager::deletingNeedToConfirm(const Akonadi::Item &item) const
{
    for (const auto &r : qAsConst(mRules)) {
        if (r.deletingNeedToConfirm(item)) {
            return true;
        }
    }
    return false;
}
