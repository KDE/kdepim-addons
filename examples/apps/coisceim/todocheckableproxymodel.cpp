/*
    This file is part of Akonadi.

    Copyright (c) 2011 Stephen Kelly <steveire@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "todocheckableproxymodel.h"

#include <AkonadiCore/EntityTreeModel>

#include <KCalCore/Todo>

using namespace Akonadi;

TodoCheckableProxyModel::TodoCheckableProxyModel(QObject *parent)
    : KCheckableProxyModel(parent)
{
}

void TodoCheckableProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    KCheckableProxyModel::setSourceModel(sourceModel);

    QItemSelectionModel *selectionModel = new QItemSelectionModel(sourceModel, this);
    setSelectionModel(selectionModel);
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &TodoCheckableProxyModel::selectionChanged);
}

void TodoCheckableProxyModel::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    setChecked(deselected, false);
    setChecked(selected, true);
}

void TodoCheckableProxyModel::setChecked(const QItemSelection &selection, bool checked)
{
    const auto listSelection = selection.indexes();
    for (const QModelIndex &index : listSelection) {
        if (index.column() == 0) {
            Item item = sourceModel()->data(index, Akonadi::EntityTreeModel::ItemRole).value<Akonadi::Item>();
            if (!item.hasPayload<KCalCore::Todo::Ptr>()) {
                continue;
            }
            KCalCore::Todo::Ptr incidence = item.payload<KCalCore::Todo::Ptr>();
            incidence->setCompleted(checked);
            sourceModel()->setData(index, QVariant::fromValue(item), Akonadi::EntityTreeModel::ItemRole);
        }
    }
}
