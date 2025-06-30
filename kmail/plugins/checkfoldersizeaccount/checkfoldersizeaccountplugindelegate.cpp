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

#include "moc_checkfoldersizeaccountplugindelegate.cpp"
