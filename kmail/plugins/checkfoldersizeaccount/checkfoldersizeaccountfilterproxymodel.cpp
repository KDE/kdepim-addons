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
    const auto collection = source_parent.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    const Akonadi::CollectionStatistics statistics = collection.statistics();
    // qDebug() << " SSSSSSSSSS " << statistics.size();
    switch (mFolderSize) {
    case FolderSize::All:
    case FolderSize::MoreThan100K:
        if (statistics.size() < 100000) {
            return false;
        }
        break;
    case FolderSize::MoreThan1M:
        if (statistics.size() < 1000000) {
            return false;
        }
        break;
    case FolderSize::MoreThan10M:
        if (statistics.size() < 10000000) {
            return false;
        }
        break;
    case FolderSize::Unknown:
        break;
    }

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
