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

#include "stackedwidgetview.h"

#include <QAbstractItemModel>
#include <QItemSelectionModel>

StackedWidgetView::StackedWidgetView(int widgetRole, QWidget *parent)
    : QStackedWidget(parent)
    , m_model(nullptr)
    , m_selectionModel(nullptr)
    , m_widgetRole(widgetRole)
{
}

void StackedWidgetView::setModel(QAbstractItemModel *model)
{
    m_model = model;

    refill();

    connect(model, &QAbstractItemModel::modelReset, this, &StackedWidgetView::refill);
    connect(model, &QAbstractItemModel::rowsInserted, this, &StackedWidgetView::insertRows);
    connect(model, &QAbstractItemModel::rowsAboutToBeRemoved, this, &StackedWidgetView::removeRows);
}

void StackedWidgetView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;

    connect(m_selectionModel, &QItemSelectionModel::selectionChanged, this, &StackedWidgetView::updateCurrentWidget);
}

void StackedWidgetView::refill()
{
    for (int i = m_model->rowCount() - 1; i >= 0; --i) {
        QWidget *w = m_model->index(i, 0).data(m_widgetRole).value<QWidget *>();
        if (w) {
            insertWidget(0, w);
        }
    }
}

void StackedWidgetView::insertRows(const QModelIndex &parent, int start, int end)
{
    for (int i = start; i <= end; ++i) {
        QWidget *w = m_model->index(i, 0, parent).data(m_widgetRole).value<QWidget *>();
        if (w) {
            insertWidget(i, w);
        }
    }
}

void StackedWidgetView::removeRows(const QModelIndex &parent, int start, int end)
{
    for (int i = start; i <= end; ++i) {
        QWidget *w = m_model->index(i, 0, parent).data(m_widgetRole).value<QWidget *>();
        if (w) {
            removeWidget(w);
        }
    }
}

void StackedWidgetView::updateCurrentWidget()
{
    const QModelIndexList list = m_selectionModel->selectedRows();

    if (list.isEmpty()) {
        return;
    }

    const QModelIndex first = list.first();
    setCurrentIndex(first.row());
}
