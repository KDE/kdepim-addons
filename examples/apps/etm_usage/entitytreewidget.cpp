/*
    Copyright (c) 2010 Stephen Kelly <steveire@gmail.com>

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

#include "entitytreewidget.h"

#include <QTreeView>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTimer>

#include <AkonadiCore/monitor.h>
#include <AkonadiCore/entitytreemodel.h>
#include <AkonadiCore/itemfetchscope.h>

using namespace Akonadi;

static const QString predefinedMimeTypes[] = {
    QLatin1String(""),
    QLatin1String("message/rfc822"),
    QLatin1String("text/directory"),
    QLatin1String("text/calendar"),
    QLatin1String("message/rfc822,text/directory")
};

static const QString predefinedUserVisibleMimeTypes[] = {
    QLatin1String("All"),
    QLatin1String("Email"),
    QLatin1String("Addressees"),
    QLatin1String("Events"),
    QLatin1String("Email and Addressees")
};

EntityTreeWidget::EntityTreeWidget(QWidget *parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_typeComboBox(new QComboBox)
    , m_typeLineEdit(new QLineEdit)
    , m_monitor(new Monitor(this))
{
    for (uint i = 0; i < sizeof predefinedMimeTypes / sizeof *predefinedMimeTypes; ++i) {
        m_typeComboBox->addItem(predefinedUserVisibleMimeTypes[i], predefinedMimeTypes[i]);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_typeComboBox);
    layout->addWidget(m_typeLineEdit);
    layout->addWidget(m_treeView);

    m_monitor->setCollectionMonitored(Collection::root());
    m_monitor->fetchCollection(true);
    m_monitor->setAllMonitored(true);
    m_monitor->itemFetchScope().fetchFullPayload(true);
    m_monitor->itemFetchScope().fetchAllAttributes(true);
    m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

EntityTreeWidget::~EntityTreeWidget()
{
}

void EntityTreeWidget::connectTreeToModel(QTreeView *tree, EntityTreeModel *model)
{
    tree->setModel(model);
}

void EntityTreeWidget::mimeTypesChoiceChanged(int index)
{
    m_typeLineEdit->setText(m_typeComboBox->itemData(index).toString());
}

void EntityTreeWidget::mimeTypesChanged(const QString &mimetypeList)
{
    const QStringList list = mimetypeList.isEmpty() ? QStringList() : mimetypeList.split(QLatin1String(","));

    foreach (const QString mimetype, m_monitor->mimeTypesMonitored()) {
        if (!list.contains(mimetype)) {
            m_monitor->setMimeTypeMonitored(mimetype, false);
        }
    }

    for (const QString &mimetype : list) {
        m_monitor->setMimeTypeMonitored(mimetype, true);
    }
}

QTreeView *EntityTreeWidget::view() const
{
    return m_treeView;
}

EntityTreeModel *EntityTreeWidget::model() const
{
    return m_etm;
}

void EntityTreeWidget::init()
{
    if (m_treeView->model()) {
        return;    // Already set up
    }

    m_etm = getETM();
    connectTreeToModel(m_treeView, m_etm);
    connect(m_typeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(mimeTypesChoiceChanged(int)));
    connect(m_typeLineEdit, SIGNAL(textChanged(QString)), SLOT(mimeTypesChanged(QString)));
}

Akonadi::Monitor *EntityTreeWidget::monitor() const
{
    return m_monitor;
}

EntityTreeModel *EntityTreeWidget::getETM()
{
    return new EntityTreeModel(m_monitor, this);
}

static int num;

void EntityTreeWidget::dumpTree()
{
    num = 1;
    qDebug() << dumpLevel(QModelIndex(), 1);
}

QString EntityTreeWidget::dumpLevel(const QModelIndex &parent, int level)
{
    const int rowCount = m_etm->rowCount(parent);
    QString lines;
    for (int row = 0; row < rowCount; ++row) {
        QString line;
        line.append(QLatin1String("\""));
        for (int l = 0; l < level; ++l) {
            line.append(QLatin1String("- "));
        }
        line.append(QString::number(num++));
        line.append(QLatin1String("\""));
        line.append(QLatin1String("\n"));
        lines.append(line);
//     qDebug() << line;
        static const int column = 0;
        const QModelIndex idx = m_etm->index(row, column, parent);
        if (m_etm->hasChildren(idx)) {
            lines.append(dumpLevel(idx, level + 1));
        }
    }
    return lines;
}
