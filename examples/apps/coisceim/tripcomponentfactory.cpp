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

#include "tripcomponentfactory.h"

#include <AkonadiCore/EntityTreeModel>
#include <AkonadiCore/Monitor>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/EntityMimeTypeFilterModel>

#include <KMime/Message>

#include <KCalCore/Todo>

#include "note.h"
#include "todocheckableproxymodel.h"
#include "mixedtreemodel.h"

Akonadi::Monitor *TripComponentFactory::createMailMonitor(QObject *parent)
{
    Akonadi::Monitor *chMon = new Akonadi::Monitor(parent);
    chMon->setMimeTypeMonitored(KMime::Message::mimeType());
    chMon->itemFetchScope().fetchFullPayload(true);
    return chMon;
}

Akonadi::Monitor *TripComponentFactory::createNotesMonitor(QObject *parent)
{
    Akonadi::Monitor *chMon = new Akonadi::Monitor(parent);
    chMon->setMimeTypeMonitored(Akonotes::Note::mimeType());
    chMon->itemFetchScope().fetchFullPayload(true);
    return chMon;
}

Akonadi::Monitor *TripComponentFactory::createTodoMonitor(QObject *parent)
{
    Akonadi::Monitor *chMon = new Akonadi::Monitor(parent);
    chMon->setMimeTypeMonitored(KCalCore::Todo::todoMimeType());
    chMon->itemFetchScope().fetchFullPayload(true);
    return chMon;
}

QAbstractItemModel *TripComponentFactory::createMailModel(Akonadi::Monitor *monitor)
{
    MixedTreeModel *model = new MixedTreeModel(monitor);
    model->setCollectionFetchStrategy(MixedTreeModel::FetchNoCollections);
    return model;
}

QAbstractItemModel *TripComponentFactory::createNotesModel(Akonadi::Monitor *monitor)
{
    MixedTreeModel *model = new MixedTreeModel(monitor);
    model->setCollectionFetchStrategy(MixedTreeModel::FetchNoCollections);
    return model;
}

QAbstractItemModel *TripComponentFactory::createTodoModel(Akonadi::Monitor *monitor)
{
    MixedTreeModel *model = new MixedTreeModel(monitor);
    model->setCollectionFetchStrategy(MixedTreeModel::FetchNoCollections);

    Akonadi::EntityMimeTypeFilterModel *filterModel = new Akonadi::EntityMimeTypeFilterModel(monitor);
    filterModel->addMimeTypeInclusionFilter(KCalCore::Todo::todoMimeType());
    filterModel->setHeaderGroup(MixedTreeModel::ItemListHeaders);
    filterModel->setSourceModel(model);

    TodoCheckableProxyModel *checkableProxy = new TodoCheckableProxyModel(model);
    checkableProxy->setSourceModel(filterModel);

    return checkableProxy;
}
