/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsplugin.h"
#include "folderconfiguresettingsdialog.h"
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(FolderConfigureSettingsPlugin, "messageviewer_folderconfiguresettingsplugin.json")

FolderConfigureSettingsPlugin::FolderConfigureSettingsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

FolderConfigureSettingsPlugin::~FolderConfigureSettingsPlugin()
{
}

void FolderConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<FolderConfigureSettingsDialog> dlg = new FolderConfigureSettingsDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "folderconfiguresettingsplugin.moc"
