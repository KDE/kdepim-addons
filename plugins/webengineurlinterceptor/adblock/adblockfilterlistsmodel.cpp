/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsmodel.h"

AdblockFilterListsModel::AdblockFilterListsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

AdblockFilterListsModel::~AdblockFilterListsModel() = default;

QList<AdblockFilter> AdblockFilterListsModel::adblockFilter() const
{
    return mAdblockFilter;
}

void AdblockFilterListsModel::setAdblockFilter(const QList<AdblockFilter> &newAdblockFilter)
{
    mAdblockFilter = newAdblockFilter;
}
