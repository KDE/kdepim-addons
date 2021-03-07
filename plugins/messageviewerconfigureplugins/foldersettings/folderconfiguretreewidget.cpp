/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguretreewidget.h"
#include "foldersettingfilterproxymodel.h"
#include <KCheckableProxyModel>
#include <MailCommon/FolderTreeView>
#include <MailCommon/FolderTreeWidget>
#include <QVBoxLayout>

FolderConfigureTreeWidget::FolderConfigureTreeWidget(QWidget *parent)
    : QWidget(parent)
    , mFolderSettingFilterProxyModel(new FolderSettingFilterProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    auto ftw = new MailCommon::FolderTreeWidget(this,
                                                nullptr,
                                                MailCommon::FolderTreeWidget::TreeViewOptions(MailCommon::FolderTreeWidget::UseDistinctSelectionModel
                                                                                              | MailCommon::FolderTreeWidget::HideStatistics
                                                                                              | MailCommon::FolderTreeWidget::HideHeaderViewMenu));
    ftw->setObjectName(QStringLiteral("foldertreewidget"));
    ftw->folderTreeView()->setDragEnabled(false);
    auto ftv = ftw->folderTreeView();
    auto sourceModel = ftv->model();
    auto selectionModel = ftw->selectionModel();

    auto checkable = new KCheckableProxyModel(this);
    checkable->setObjectName(QStringLiteral("checkable"));
    checkable->setSourceModel(sourceModel);
    checkable->setSelectionModel(selectionModel);

    mFolderSettingFilterProxyModel->setObjectName(QStringLiteral("folderSettingFilterProxyModel"));
    mFolderSettingFilterProxyModel->setSourceModel(checkable);

    ftv->setModel(mFolderSettingFilterProxyModel);
    ftv->expandAll();

    mainLayout->addWidget(ftw);
}

FolderConfigureTreeWidget::~FolderConfigureTreeWidget()
{
}

Akonadi::Collection::List FolderConfigureTreeWidget::listCollections() const
{
    return mFolderSettingFilterProxyModel->listCollections();
}
