/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsview.h"
#include "adblockfilterlistsmodel.h"
#include "adblockmanager.h"

AdblockFilterListsView::AdblockFilterListsView(QWidget *parent)
    : QListView(parent)
    , mAdblockFilterListsModel(new AdblockFilterListsModel(this))
{
    mAdblockFilterListsModel->setObjectName(QStringLiteral("mAdblockFilterListsModel"));
    mAdblockFilterListsModel->setAdblockFilter(AdblockManager::self()->adblockFilterLists());
    setModel(mAdblockFilterListsModel);
}

AdblockFilterListsView::~AdblockFilterListsView() = default;

#include "moc_adblockfilterlistsview.cpp"
