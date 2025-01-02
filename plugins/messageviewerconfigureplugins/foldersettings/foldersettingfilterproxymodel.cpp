/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "foldersettingfilterproxymodel.h"
#include <Akonadi/EntityTreeModel>

FolderSettingFilterProxyModel::FolderSettingFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

FolderSettingFilterProxyModel::~FolderSettingFilterProxyModel() = default;

QVariant FolderSettingFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::CheckStateRole) {
        // Make top-level collections uncheckable
        const auto col = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
        if (col.parentCollection() == Akonadi::Collection::root()) {
            return {};
        }
    }

    return QSortFilterProxyModel::data(index, role);
}

Qt::ItemFlags FolderSettingFilterProxyModel::flags(const QModelIndex &index) const
{
    // Make top-level collections uncheckable
    const auto col = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (col.parentCollection() == Akonadi::Collection::root()) {
        return QSortFilterProxyModel::flags(index) & ~Qt::ItemIsUserCheckable;
    } else {
        return QSortFilterProxyModel::flags(index);
    }
}

Akonadi::Collection::List FolderSettingFilterProxyModel::listCollections() const
{
    return mListCollections;
}

bool FolderSettingFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole) {
        if (index.isValid()) {
            const auto collection = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
            if (value == Qt::Checked) {
                mListCollections.append(collection);
            } else {
                mListCollections.removeAll(collection);
            }
            Q_EMIT dataChanged(index, index);
        }
    }

    return QSortFilterProxyModel::setData(index, value, role);
}

#include "moc_foldersettingfilterproxymodel.cpp"
