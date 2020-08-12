/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
