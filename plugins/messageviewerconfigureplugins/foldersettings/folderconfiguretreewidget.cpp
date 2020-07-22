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

#include "folderconfiguretreewidget.h"
#include "foldersettingfilterproxymodel.h"
#include <QVBoxLayout>
#include <KCheckableProxyModel>
#include <MailCommon/FolderTreeWidget>
#include <MailCommon/FolderTreeView>

FolderConfigureTreeWidget::FolderConfigureTreeWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    auto ftw = new MailCommon::FolderTreeWidget(this, nullptr,
                                                MailCommon::FolderTreeWidget::TreeViewOptions(MailCommon::FolderTreeWidget::UseDistinctSelectionModel
                                                                                              |MailCommon::FolderTreeWidget::HideStatistics
                                                                                              |MailCommon::FolderTreeWidget::HideHeaderViewMenu));
    ftw->setObjectName(QStringLiteral("foldertreewidget"));
    ftw->folderTreeView()->setDragEnabled(false);
    auto ftv = ftw->folderTreeView();
    auto sourceModel = ftv->model();
    auto selectionModel = ftw->selectionModel();

    auto checkable = new KCheckableProxyModel(this);
    checkable->setObjectName(QStringLiteral("checkable"));
    checkable->setSourceModel(sourceModel);
    checkable->setSelectionModel(selectionModel);


    auto folderSettingFilterProxyModel = new FolderSettingFilterProxyModel(this);
    folderSettingFilterProxyModel->setObjectName(QStringLiteral("folderSettingFilterProxyModel"));
    folderSettingFilterProxyModel->setSourceModel(checkable);

    ftv->setModel(folderSettingFilterProxyModel);
    ftv->expandAll();


    mainLayout->addWidget(ftw);
}

FolderConfigureTreeWidget::~FolderConfigureTreeWidget()
{

}
