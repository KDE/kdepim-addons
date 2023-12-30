/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsmodel.h"

#include <KLocalizedString>

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
    beginInsertRows(QModelIndex(), numberOfElement, mAdblockFilter.count());
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
    Q_UNUSED(parent)
    constexpr int val = static_cast<int>(AdblockFilterRole::LastColumn) + 1;
    return val;
}

QVariant AdblockFilterListsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mAdblockFilter.count()) {
        return {};
    }
    if (role != Qt::DisplayRole) {
        return {};
    }

    const AdblockFilter &adblockFilter = mAdblockFilter.at(index.row());
    const int col = index.column();
    switch (static_cast<AdblockFilterRole>(col)) {
    case AdblockFilterRole::Name:
        return adblockFilter.name();
    case AdblockFilterRole::Url:
        return adblockFilter.url();
    }
    return {};
}

QVariant AdblockFilterListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (static_cast<AdblockFilterRole>(section)) {
        case AdblockFilterRole::Name:
            return i18nc("@title:column", "Name");
        case AdblockFilterRole::Url:
            return i18nc("@title:column", "Url");
        }
    }
    return {};
}

#include "moc_adblockfilterlistsmodel.cpp"
