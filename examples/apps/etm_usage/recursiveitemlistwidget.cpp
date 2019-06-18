/*
    Copyright (C) 2010 Klarälvdalens Datakonsult AB,
        a KDAB Group company, info@kdab.net,
        author Stephen Kelly <stephen@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

// READ THE README FILE

#include "recursiveitemlistwidget.h"

#include <QHBoxLayout>

#include <AkonadiCore/entitytreemodel.h>
#include <AkonadiCore/entitymimetypefiltermodel.h>
#include <AkonadiCore/monitor.h>

#include <Akonadi/Contact/ContactsTreeModel>
#include <AkonadiWidgets/entitylistview.h>
#include <AkonadiWidgets/entitytreeview.h>
#include <KContacts/Addressee>
#include <AkonadiCore/ItemFetchScope>

RecursiveItemListWidget::RecursiveItemListWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    Akonadi::Monitor *monitor = new Akonadi::Monitor(this);
    monitor->setAllMonitored(true);
    monitor->setMimeTypeMonitored(KContacts::Addressee::mimeType());
    monitor->itemFetchScope().fetchFullPayload(true);
    m_etm = new Akonadi::ContactsTreeModel(monitor, this);

    m_etm->setCollectionFetchStrategy(Akonadi::EntityTreeModel::InvisibleCollectionFetch);

    Akonadi::EntityMimeTypeFilterModel *list = new Akonadi::EntityMimeTypeFilterModel(this);
    list->setSourceModel(m_etm);
    list->setHeaderGroup(Akonadi::EntityTreeModel::ItemListHeaders);

    m_listView = new Akonadi::EntityTreeView;
    m_listView->setModel(list);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_listView);
}
