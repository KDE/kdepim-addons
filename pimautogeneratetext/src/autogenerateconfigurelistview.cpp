/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigurelistview.h"
#include "autogenerateconfigureaskmodel.h"
#include <QSortFilterProxyModel>
AutogenerateConfigureListView::AutogenerateConfigureListView(QWidget *parent)
    : QListView(parent)
    , mModel(new AutogenerateConfigureAskModel(this))
{
    auto sortFilter = new QSortFilterProxyModel(this);
    sortFilter->setSourceModel(mModel);
    setModel(sortFilter);
}

AutogenerateConfigureListView::~AutogenerateConfigureListView() = default;

#include "moc_autogenerateconfigurelistview.cpp"
