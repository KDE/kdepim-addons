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
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mSortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSortFilterProxyModel->setSourceModel(mModel);
    setModel(mSortFilterProxyModel);
}

AutogenerateConfigureListView::~AutogenerateConfigureListView() = default;

void AutogenerateConfigureListView::setFilterText(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

#include "moc_autogenerateconfigurelistview.cpp"
