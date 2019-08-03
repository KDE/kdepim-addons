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

#include "trip.h"

#include <QSortFilterProxyModel>

#include <AkonadiCore/Monitor>

#include <KCalendarCore/Incidence>

#include "tripcomponentfactory.h"
#include "tripmodel.h"
#include <QItemSelectionModel>
#include "itemviewerwidget.h"
#include "qmllistselectionmodel.h"
#include <QTreeView>

using namespace Akonadi;

Trip::Trip(const QPersistentModelIndex &index, Akonadi::Monitor *monitor, TripComponentFactory *factory, QObject *parent)
    : QObject(parent)
    , m_index(index)
    , m_monitor(monitor)
{
    QAbstractItemModel *model = const_cast<QAbstractItemModel *>(m_index.model());
    connect(model, &QAbstractItemModel::dataChanged, this, &Trip::dataChanged);
    connect(model, &QAbstractItemModel::modelReset, this, &Trip::modelReset);
    connect(model, &QAbstractItemModel::layoutChanged, this, &Trip::layoutChanged);
    connect(model, &QAbstractItemModel::rowsRemoved, this, &Trip::rowsRemoved);

    m_mailMonitor = factory->createMailMonitor(this);
    m_todoMonitor = factory->createTodoMonitor(this);
    m_notesMonitor = factory->createNotesMonitor(this);

    m_mailMonitor->setSession(m_monitor->session());
    m_todoMonitor->setSession(m_monitor->session());
    m_notesMonitor->setSession(m_monitor->session());

    m_mailModel = new QSortFilterProxyModel(this);
    m_mailModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_todoModel = new QSortFilterProxyModel(this);
    m_todoModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_notesModel = new QSortFilterProxyModel(this);
    m_notesModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    m_mailModel->setSourceModel(factory->createMailModel(m_mailMonitor));
    m_todoModel->setSourceModel(factory->createTodoModel(m_todoMonitor));
    m_notesModel->setSourceModel(factory->createNotesModel(m_notesMonitor));

    QItemSelectionModel *mailItemSelection = new QItemSelectionModel(m_mailModel, this);
    QItemSelectionModel *todoItemSelection = new QItemSelectionModel(m_todoModel, this);
    QItemSelectionModel *notesItemSelection = new QItemSelectionModel(m_notesModel, this);

    m_mailSelection = new QMLListSelectionModel(mailItemSelection, this);
    m_todoSelection = new QMLListSelectionModel(todoItemSelection, this);
    m_notesSelection = new QMLListSelectionModel(notesItemSelection, this);

    m_itemSelection = new ItemSelection(mailItemSelection, todoItemSelection, notesItemSelection, this);

    updateEvent();
}

QModelIndex Trip::index() const
{
    return m_index;
}

void Trip::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    if (topLeft.parent() == m_index.parent()) {
        if (topLeft.row() <= m_index.row() && bottomRight.row() >= m_index.row()) {
            updateEvent();
        }
    }
}

QString Trip::eventDescription() const
{
    return m_eventDescription;
}

QString Trip::eventName() const
{
    return m_eventName;
}

void Trip::layoutChanged()
{
    updateEvent();
}

void Trip::modelReset()
{
    m_eventDescription.clear();
    Q_EMIT eventDescriptionChanged();
    m_eventName.clear();
    Q_EMIT eventNameChanged();
}

void Trip::rowsRemoved(const QModelIndex &parent, int start, int end)
{
    if (parent == m_index.parent() && start <= m_index.row() && end >= m_index.row()) {
        updateEvent();
    }
}

void Trip::updateEvent()
{
    Akonadi::Item item = m_index.data(Akonadi::EntityTreeModel::ItemRole).value<Akonadi::Item>();
    if (!item.hasPayload<KCalendarCore::Incidence::Ptr>()) {
        return;
    }
    KCalendarCore::Incidence::Ptr incidence = item.payload<KCalendarCore::Incidence::Ptr>();
    setEventDescription(incidence->description());
    setEventName(incidence->summary());
}

static void updateCollection(Akonadi::Monitor *mon, const Collection &collection)
{
    for (const Collection &existingCollection : mon->collectionsMonitored()) {
        mon->setCollectionMonitored(existingCollection, false);
    }

    for (const QString &mimeType : mon->mimeTypesMonitored()) {
        mon->setMimeTypeMonitored(mimeType, false);
    }

    if (collection.isValid()) {
        mon->setCollectionMonitored(collection, true);
    }
}

void Trip::setCollection(int role, const Akonadi::Collection &collection)
{
    switch (role) {
    case MailCollectionRole:
        updateCollection(m_mailMonitor, collection);
        Q_EMIT monitoredCollectionsChanged();
        return;
    case TodoCollectionRole:
        updateCollection(m_todoMonitor, collection);
        Q_EMIT monitoredCollectionsChanged();
        return;
    case NotesCollectionRole:
        updateCollection(m_notesMonitor, collection);
        Q_EMIT monitoredCollectionsChanged();
        return;
    }
}

static Akonadi::Collection monitoredCollection(Akonadi::Monitor *monitor)
{
    Akonadi::Collection::List list = monitor->collectionsMonitored();
    if (list.isEmpty()) {
        return Akonadi::Collection(-1);
    }
    return list.first();
}

Akonadi::Collection Trip::collection(int role)
{
    switch (role) {
    case MailCollectionRole:
        return monitoredCollection(m_mailMonitor);
    case TodoCollectionRole:
        return monitoredCollection(m_todoMonitor);
    case NotesCollectionRole:
        return monitoredCollection(m_notesMonitor);
    }
    return Akonadi::Collection();
}

QAbstractItemModel *Trip::mailModel() const
{
    return m_mailModel;
}

QAbstractItemModel *Trip::notesModel() const
{
    return m_notesModel;
}

QAbstractItemModel *Trip::todoModel() const
{
    return m_todoModel;
}

QObject *Trip::scriptableMailModel() const
{
    return m_mailModel;
}

QObject *Trip::scriptableNotesModel() const
{
    return m_notesModel;
}

QObject *Trip::scriptableTodoModel() const
{
    return m_todoModel;
}

qint64 Trip::id() const
{
    return m_index.data(EntityTreeModel::ItemIdRole).toLongLong();
}

void Trip::setEventName(const QString &name)
{
    if (m_eventName != name) {
        m_eventName = name;
        Q_EMIT eventNameChanged();
    }
}

void Trip::setEventDescription(const QString &description)
{
    if (m_eventDescription != description) {
        m_eventDescription = description;
        Q_EMIT eventDescriptionChanged();
    }
}

void Trip::setComponentFilter(const QString &filter)
{
    m_mailModel->setFilterRegExp(filter);
    m_todoModel->setFilterRegExp(filter);
    m_notesModel->setFilterRegExp(filter);
}

QObject *Trip::itemSelection() const
{
    return m_itemSelection;
}

QObject *Trip::mailSelection() const
{
    return m_mailSelection;
}

QObject *Trip::todoSelection() const
{
    return m_todoSelection;
}

QObject *Trip::notesSelection() const
{
    return m_notesSelection;
}
