/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguretreewidget.h"
#include "foldersettingfilterproxymodel.h"
#include <KCheckableProxyModel>
#include <KLocalizedString>
#include <MailCommon/FolderTreeView>
#include <MailCommon/FolderTreeWidget>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>

FolderConfigureTreeWidget::FolderConfigureTreeWidget(QWidget *parent)
    : QWidget(parent)
    , mFolderSettingFilterProxyModel(new FolderSettingFilterProxyModel(this))
    , mFolderTreeWidget(new MailCommon::FolderTreeWidget(this,
                                                         nullptr,
                                                         MailCommon::FolderTreeWidget::TreeViewOptions(MailCommon::FolderTreeWidget::UseDistinctSelectionModel
                                                                                                       | MailCommon::FolderTreeWidget::HideStatistics
                                                                                                       | MailCommon::FolderTreeWidget::HideHeaderViewMenu)))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    mFolderTreeWidget->setObjectName(QStringLiteral("foldertreewidget"));
    mFolderTreeWidget->folderTreeView()->setDragEnabled(false);
    mFolderTreeWidget->folderTreeView()->setSelectionMode(QAbstractItemView::ExtendedSelection);

    auto ftv = mFolderTreeWidget->folderTreeView();
    auto sourceModel = ftv->model();
    auto selectionModel = mFolderTreeWidget->selectionModel();

    auto checkable = new KCheckableProxyModel(this);
    checkable->setObjectName(QStringLiteral("checkable"));
    checkable->setSourceModel(sourceModel);
    checkable->setSelectionModel(selectionModel);

    mFolderSettingFilterProxyModel->setObjectName(QStringLiteral("folderSettingFilterProxyModel"));
    mFolderSettingFilterProxyModel->setSourceModel(checkable);

    ftv->setModel(mFolderSettingFilterProxyModel);
    ftv->expandAll();
    mainLayout->addWidget(mFolderTreeWidget);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
    mainLayout->addLayout(buttonLayout);

    auto selectFolder = new QPushButton(i18n("Select"), this);
    selectFolder->setObjectName(QStringLiteral("selectFolder"));
    buttonLayout->addWidget(selectFolder);
    connect(selectFolder, &QPushButton::clicked, this, [this]() {
        changeFolderSelection(true);
    });

    auto unSelectFolder = new QPushButton(i18n("Unselect"), this);
    unSelectFolder->setObjectName(QStringLiteral("unSelectFolder"));
    buttonLayout->addWidget(unSelectFolder);
    connect(unSelectFolder, &QPushButton::clicked, this, [this]() {
        changeFolderSelection(false);
    });
}

FolderConfigureTreeWidget::~FolderConfigureTreeWidget()
{
}

void FolderConfigureTreeWidget::changeFolderSelection(bool select)
{
    const QModelIndexList indexes = mFolderTreeWidget->folderTreeView()->selectionModel()->selectedIndexes();
    for (const QModelIndex &selectedIndex : indexes) {
        mFolderSettingFilterProxyModel->setData(selectedIndex, select ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
    }
}

Akonadi::Collection::List FolderConfigureTreeWidget::listCollections() const
{
    return mFolderSettingFilterProxyModel->listCollections();
}
