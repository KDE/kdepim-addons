/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugin.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CheckFolderSizeAccountPlugin, "kmail_checkfoldersizeaccountplugin.json")

CheckFolderSizeAccountPlugin::CheckFolderSizeAccountPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin{parent}
{
}

PimCommon::GenericPluginInterface *CheckFolderSizeAccountPlugin::createInterface(QObject *parent)
{
    // TODO
    return nullptr;
}

CheckFolderSizeAccountPlugin::~CheckFolderSizeAccountPlugin() = default;

#include "checkfoldersizeaccountplugin.moc"
#include "moc_checkfoldersizeaccountplugin.cpp"
