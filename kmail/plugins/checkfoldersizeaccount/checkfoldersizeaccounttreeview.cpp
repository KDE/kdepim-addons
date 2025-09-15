/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccounttreeview.h"
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
        /*
        menu.addAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove"), this, [this, index]() {
            const QModelIndex modelIndex = model()->index(index.row(), AdminInviteModel::Identifier);
            removeClicked(modelIndex.data().toByteArray());
        });
        */
        menu.exec(viewport()->mapToGlobal(pos));
    }
}

#include "moc_checkfoldersizeaccounttreeview.cpp"
