/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigurelistview.h"
#include "autogenerateconfigureaskmodel.h"
#include "autogenerateconfigurelistviewdelegate.h"
#include <QSortFilterProxyModel>
AutogenerateConfigureListView::AutogenerateConfigureListView(QWidget *parent)
    : QListView(parent)
    , mModel(new AutogenerateConfigureAskModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mSortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSortFilterProxyModel->setSourceModel(mModel);
    setModel(mSortFilterProxyModel);
    setItemDelegate(new AutogenerateConfigureListViewDelegate(this));
}

AutogenerateConfigureListView::~AutogenerateConfigureListView() = default;

void AutogenerateConfigureListView::setFilterText(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

QList<AutogenerateConfigureAskItem> AutogenerateConfigureListView::askItems() const
{
    return mModel->askItems();
}

void AutogenerateConfigureListView::setAskItems(const QList<AutogenerateConfigureAskItem> &newAskItems)
{
    mModel->setAskItems(newAskItems);
}

#include "moc_autogenerateconfigurelistview.cpp"
