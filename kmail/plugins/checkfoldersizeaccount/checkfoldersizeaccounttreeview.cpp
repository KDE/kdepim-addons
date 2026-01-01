/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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
            const auto collectionId = index.data(Akonadi::EntityTreeModel::CollectionIdRole).toLongLong();
            // qDebug() << "collectionId " << collectionId;
            auto job = CheckFolderSizeAccountPluginOpenFolderJob(QString::number(collectionId), this);
            job.start();
        });

        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_checkfoldersizeaccounttreeview.cpp"
