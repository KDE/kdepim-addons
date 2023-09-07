/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsview.h"
#include "adblockfilterlistsmodel.h"
#include "adblockmanager.h"
#include <QSortFilterProxyModel>

AdblockFilterListsView::AdblockFilterListsView(QWidget *parent)
    : QListView(parent)
    , mAdblockFilterListsModel(new AdblockFilterListsModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mAdblockFilterListsModel->setObjectName(QStringLiteral("mAdblockFilterListsModel"));

    mSortFilterProxyModel->setObjectName(QStringLiteral("mSortFilterProxyModel"));

    mAdblockFilterListsModel->setAdblockFilter(AdblockManager::self()->adblockFilterLists());
    mSortFilterProxyModel->setSourceModel(mAdblockFilterListsModel);
    setModel(mSortFilterProxyModel);
}

AdblockFilterListsView::~AdblockFilterListsView() = default;

void AdblockFilterListsView::setFilterString(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

#include "moc_adblockfilterlistsview.cpp"
