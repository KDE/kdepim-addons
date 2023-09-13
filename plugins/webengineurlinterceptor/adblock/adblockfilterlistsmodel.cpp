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

void AdblockFilterListsModel::removeList(const QString &identifier)
{
    const int roomCount = mAdblockFilter.count();
    for (int i = 0; i < roomCount; ++i) {
        if (mAdblockFilter.at(i).name() == identifier) {
            beginRemoveRows(QModelIndex(), i, i);
            mAdblockFilter.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void AdblockFilterListsModel::insertList(const AdblockFilter &filter)
{
    const int numberOfElement = mAdblockFilter.count();
    mAdblockFilter.append(filter);
    beginInsertRows(QModelIndex(), numberOfElement, mAdblockFilter.count() - 1);
    endInsertRows();
}

void AdblockFilterListsModel::setAdblockFilter(const QList<AdblockFilter> &newAdblockFilter)
{
    mAdblockFilter = newAdblockFilter;
}

int AdblockFilterListsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mAdblockFilter.count();
}

QVariant AdblockFilterListsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mAdblockFilter.count()) {
        return {};
    }
    const AdblockFilter &adblockFilter = mAdblockFilter.at(index.row());
    switch (role) {
    case UrlRole:
        return adblockFilter.url();
    }
    return {};
}

#include "moc_adblockfilterlistsmodel.cpp"
