/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugininterface.h"

CheckFolderSizeAccountPluginInterface::CheckFolderSizeAccountPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface{parent}
{
}

CheckFolderSizeAccountPluginInterface::~CheckFolderSizeAccountPluginInterface() = default;

void CheckFolderSizeAccountPluginInterface::exec()
{
    // TODO
}

void CheckFolderSizeAccountPluginInterface::createAction(KActionCollection *ac)
{
    // TODO
}
