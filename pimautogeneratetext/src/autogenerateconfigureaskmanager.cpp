/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigureaskmanager.h"

AutogenerateConfigureAskManager::AutogenerateConfigureAskManager(QObject *parent)
    : QObject{parent}
{
}

AutogenerateConfigureAskManager::~AutogenerateConfigureAskManager() = default;

void AutogenerateConfigureAskManager::load()
{
}

void AutogenerateConfigureAskManager::save()
{
}

QList<AutogenerateConfigureAskItem> AutogenerateConfigureAskManager::items() const
{
    return mItems;
}

void AutogenerateConfigureAskManager::setItems(const QList<AutogenerateConfigureAskItem> &newItems)
{
    if (mItems != newItems) {
        mItems = newItems;
        Q_EMIT changed();
    }
}

#include "moc_autogenerateconfigureaskmanager.cpp"
