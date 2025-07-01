/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountfilterproxymodel.h"

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

#include "moc_checkfoldersizeaccountfilterproxymodel.cpp"
