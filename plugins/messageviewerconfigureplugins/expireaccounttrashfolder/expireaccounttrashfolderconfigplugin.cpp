/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expireaccounttrashfolderconfigplugin.h"
#include "expireaccounttrashfolderconfigdialog.h"
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(ExpireAccountTrashFolderConfigPlugin, "messageviewer_expireaccounttrashfolderconfigplugin.json")

ExpireAccountTrashFolderConfigPlugin::ExpireAccountTrashFolderConfigPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

ExpireAccountTrashFolderConfigPlugin::~ExpireAccountTrashFolderConfigPlugin()
{
}

void ExpireAccountTrashFolderConfigPlugin::showConfigureDialog(QWidget *parent)
{
    ExpireAccountTrashFolderConfigDialog dlg(parent);
    dlg.exec();
}

#include "expireaccounttrashfolderconfigplugin.moc"
