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
    addItem(i18nc("@label:combobox, All folders", "All"), CheckFolderSizeAccountFilterProxyModel::FolderSize::All);
    addItem(i18nc("@label:combobox, Folders bigger than the specified size", "More Than 100 kB"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan100K);
    addItem(i18nc("@label:combobox, Folders bigger than the specified size", "More Than 1 MB"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan1M);
    addItem(i18nc("@label:combobox, Folders bigger than the specified size", "More Than 10 MB"), CheckFolderSizeAccountFilterProxyModel::FolderSize::MoreThan10M);
}

CheckFolderSizeAccountFilterProxyModel::FolderSize CheckFolderSizeAccountComboBox::currentFolderSize() const
{
    return currentData().value<CheckFolderSizeAccountFilterProxyModel::FolderSize>();
}

#include "moc_checkfoldersizeaccountcombobox.cpp"
