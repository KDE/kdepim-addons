/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccounttreeview.h"
#include "checkfoldersizeaccountpluginopenfolderjob.h"
#include <Akonadi/EntityTreeModel>
#include <KLocalizedString>
#include <QMenu>
using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountTreeView::CheckFolderSizeAccountTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &CheckFolderSizeAccountTreeView::customContextMenuRequested, this, &CheckFolderSizeAccountTreeView::slotCustomContextMenuRequested);
}

CheckFolderSizeAccountTreeView::~CheckFolderSizeAccountTreeView() = default;

void CheckFolderSizeAccountTreeView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        QMenu menu(this);
        menu.addAction(i18nc("@action", "Open Folder"), this, [this, index]() {
            qDebug() << " ssssssssssss index " << index;
            const QModelIndex modelIndex = model()->index(index.row(), Akonadi::EntityTreeModel::CollectionIdRole);
            qDebug() << " modelIndex " << modelIndex;
            auto job = CheckFolderSizeAccountPluginOpenFolderJob(modelIndex.data().toString(), this);
            job.start();
        });

        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_checkfoldersizeaccounttreeview.cpp"
