/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "foldersettingfilterproxymodel.h"
#include <AkonadiCore/EntityTreeModel>

FolderSettingFilterProxyModel::FolderSettingFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

FolderSettingFilterProxyModel::~FolderSettingFilterProxyModel()
{
}

QVariant FolderSettingFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::CheckStateRole) {
        // Make top-level collections uncheckable
        const Akonadi::Collection col = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
        if (col.parentCollection() == Akonadi::Collection::root()) {
            return {};
        }
    }

    return QSortFilterProxyModel::data(index, role);
}

Qt::ItemFlags FolderSettingFilterProxyModel::flags(const QModelIndex &index) const
{
    // Make top-level collections uncheckable
    const Akonadi::Collection col = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (col.parentCollection() == Akonadi::Collection::root()) {
        return QSortFilterProxyModel::flags(index) & ~Qt::ItemIsUserCheckable;
    } else {
        return QSortFilterProxyModel::flags(index);
    }
}

bool FolderSettingFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole) {
        if (index.isValid()) {
            const Akonadi::Collection collection
                = data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
            //mNotificationCollection[collection] = (value == Qt::Checked);
            qDebug() << " collectionId " << collection.id();
            Q_EMIT dataChanged(index, index);
            //return true;
        }
    }

    return QSortFilterProxyModel::setData(index, value, role);
}
