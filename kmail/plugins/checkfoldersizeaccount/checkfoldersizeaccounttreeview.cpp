/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccounttreeview.h"
#include "checkfoldersizeaccountpluginopenfolderjob.h"
#include <KLocalizedString>
#include <QMenu>
using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountTreeView::CheckFolderSizeAccountTreeView(QWidget *parent)
    : QTreeView(parent)
{
    connect(this, &CheckFolderSizeAccountTreeView::customContextMenuRequested, this, &CheckFolderSizeAccountTreeView::slotCustomContextMenuRequested);
}

CheckFolderSizeAccountTreeView::~CheckFolderSizeAccountTreeView() = default;

void CheckFolderSizeAccountTreeView::slotCustomContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        QMenu menu(this);
        menu.addAction(i18nc("@action", "Open Folder"), this, [this, index]() {
            // TODO const QModelIndex modelIndex = model()->index(index.row(), AdminInviteModel::Identifier);
            auto job = CheckFolderSizeAccountPluginOpenFolderJob(u""_s, this);
            job.start();
        });

        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_checkfoldersizeaccounttreeview.cpp"
