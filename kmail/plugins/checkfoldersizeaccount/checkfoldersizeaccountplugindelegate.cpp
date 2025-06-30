/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountplugindelegate.h"

CheckFolderSizeAccountPluginDelegate::CheckFolderSizeAccountPluginDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

CheckFolderSizeAccountPluginDelegate::~CheckFolderSizeAccountPluginDelegate() = default;

void CheckFolderSizeAccountPluginDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO
}

#include "moc_checkfoldersizeaccountplugindelegate.cpp"
