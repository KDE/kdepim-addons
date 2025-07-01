/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountcombobox.h"
#include <KLocalizedString>

CheckFolderSizeAccountComboBox::CheckFolderSizeAccountComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

CheckFolderSizeAccountComboBox::~CheckFolderSizeAccountComboBox() = default;

void CheckFolderSizeAccountComboBox::fill()
{
    addItem(i18n("All"), CheckFolderSizeAccountFilterProxyModel::FolderSize::All);
    addItem(i18n("More Than 100Ko"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan100K);
    addItem(i18n("More Than 1Mo"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan1M);
    addItem(i18n("More Than 10Mo"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan10M);
}

CheckFolderSizeAccountFilterProxyModel::FolderSize CheckFolderSizeAccountComboBox::currentFolderSize() const
{
    return currentData().value<CheckFolderSizeAccountFilterProxyModel::FolderSize>();
}

#include "moc_checkfoldersizeaccountcombobox.cpp"
