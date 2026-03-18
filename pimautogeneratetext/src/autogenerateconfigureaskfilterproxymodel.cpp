/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskfilterproxymodel.h"
#include "autogenerateconfigureaskmodel.h"

AutogenerateConfigureAskFilterProxyModel::AutogenerateConfigureAskFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

AutogenerateConfigureAskFilterProxyModel::~AutogenerateConfigureAskFilterProxyModel() = default;

bool AutogenerateConfigureAskFilterProxyModel::moveRows(const QModelIndex &sourceParent,
                                                        int sourceRow,
                                                        int count,
                                                        const QModelIndex &destinationParent,
                                                        int destinationChild)
{
    const int srcRow = mapToSource(index(sourceRow, 0, sourceParent)).row();
    const int destRow = destinationChild < rowCount(destinationParent) ? mapToSource(index(destinationChild, 0, destinationParent)).row()
                                                                       : sourceModel()->rowCount(mapToSource(destinationParent));
    return sourceModel()->moveRows(mapToSource(sourceParent), srcRow, count, mapToSource(destinationParent), destRow);
}

bool AutogenerateConfigureAskFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (!sourceModel()) {
        return false;
    }
    if (left.parent().isValid() && right.parent().isValid()) {
        const qint64 leftOrder = sourceModel()->data(left, AutogenerateConfigureAskModel::OrderRole).toInt();
        const qint64 rightOrder = sourceModel()->data(right, AutogenerateConfigureAskModel::OrderRole).toInt();
        return leftOrder < rightOrder;
    }
    return left.row() < right.row();
}

#include "moc_autogenerateconfigureaskfilterproxymodel.cpp"
