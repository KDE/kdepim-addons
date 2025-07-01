/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugin.h"
#include "checkfoldersizeaccountpluginconfiguredialog.h"
#include "checkfoldersizeaccountplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CheckFolderSizeAccountPlugin, "kmail_checkfoldersizeaccountplugin.json")

CheckFolderSizeAccountPlugin::CheckFolderSizeAccountPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin{parent}
{
}

CheckFolderSizeAccountPlugin::~CheckFolderSizeAccountPlugin() = default;

PimCommon::GenericPluginInterface *CheckFolderSizeAccountPlugin::createInterface(QObject *parent)
{
    return new CheckFolderSizeAccountPluginInterface(parent);
}

bool CheckFolderSizeAccountPlugin::hasConfigureDialog() const
{
    return true;
}

void CheckFolderSizeAccountPlugin::showConfigureDialog(QWidget *parent)
{
    CheckFolderSizeAccountPluginConfigureDialog dlg(parent);
    dlg.exec();
}

#include "checkfoldersizeaccountplugin.moc"
#include "moc_checkfoldersizeaccountplugin.cpp"
