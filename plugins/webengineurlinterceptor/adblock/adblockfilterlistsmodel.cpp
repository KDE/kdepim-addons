/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsmodel.h"

#include <KLocalizedString>

AdblockFilterListsModel::AdblockFilterListsModel(QObject *parent)
    : QAbstractTableModel{parent}
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
    beginInsertRows(QModelIndex(), numberOfElement, mAdblockFilter.count() - 1);
    mAdblockFilter.append(filter);
    endInsertRows();
}

void AdblockFilterListsModel::setAdblockFilter(const QList<AdblockFilter> &newAdblockFilter)
{
    beginResetModel();
    mAdblockFilter = newAdblockFilter;
    endResetModel();
}

int AdblockFilterListsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mAdblockFilter.count();
}

int AdblockFilterListsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return 2;
}

QVariant AdblockFilterListsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mAdblockFilter.count()) {
        return {};
    }
    const AdblockFilter &adblockFilter = mAdblockFilter.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return index.column() == 0 ? adblockFilter.name() : adblockFilter.url();
    }
    return {};
}

QVariant AdblockFilterListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    if (section == 0) {
        return i18nc("@title:column", "Name");
    } else {
        return i18nc("@title:column", "Url");
    }
}

#include "moc_adblockfilterlistsmodel.cpp"
