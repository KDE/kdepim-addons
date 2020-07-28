/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguresettingswidget.h"
#include "folderconfiguretreewidget.h"
#include <QHBoxLayout>
#include <QSplitter>

FolderConfigureSettingsWidget::FolderConfigureSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    //TODO add label ?

    QSplitter *splitter = new QSplitter(this);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setChildrenCollapsible(false);
    mainLayout->addWidget(splitter);

    mFolderConfigureTreeWidget = new FolderConfigureTreeWidget(this);
    mFolderConfigureTreeWidget->setObjectName(QStringLiteral("mFolderConfigureTreeWidget"));
    splitter->addWidget(mFolderConfigureTreeWidget);


    mFolderConfigureSettingsPageWidget = new FolderConfigureSettingsPageWidget(this);
    mFolderConfigureSettingsPageWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsPageWidget"));
    splitter->addWidget(mFolderConfigureSettingsPageWidget);


}

FolderConfigureSettingsWidget::~FolderConfigureSettingsWidget()
{

}

void FolderConfigureSettingsWidget::save()
{
#if 0
    const auto indexes = checkable->selectionModel()->selectedIndexes();
    QSet<qint64> list;
    list.reserve(indexes.count());
    for (const auto &index : indexes) {
        list << index.data(Akonadi::EntityTreeModel::CollectionIdRole).toLongLong();
    }
#endif
    //TODO
}
