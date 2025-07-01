/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountfilterproxymodel.h"
#include <Akonadi/Collection>
#include <Akonadi/CollectionStatistics>
#include <Akonadi/EntityTreeModel>

CheckFolderSizeAccountFilterProxyModel::CheckFolderSizeAccountFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setRecursiveFilteringEnabled(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(Qt::DisplayRole);
    setSortCaseSensitivity(Qt::CaseSensitive);
    setSortLocaleAware(true);
}

CheckFolderSizeAccountFilterProxyModel::~CheckFolderSizeAccountFilterProxyModel() = default;

bool CheckFolderSizeAccountFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

CheckFolderSizeAccountFilterProxyModel::FolderSize CheckFolderSizeAccountFilterProxyModel::folderSize() const
{
    return mFolderSize;
}

void CheckFolderSizeAccountFilterProxyModel::setFolderSize(const FolderSize &newFolderSize)
{
    if (mFolderSize != newFolderSize) {
        mFolderSize = newFolderSize;
        invalidateFilter();
    }
}

#include "moc_checkfoldersizeaccountfilterproxymodel.cpp"
