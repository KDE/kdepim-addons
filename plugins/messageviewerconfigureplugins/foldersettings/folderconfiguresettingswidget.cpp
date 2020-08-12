/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
