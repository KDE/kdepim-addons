/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
