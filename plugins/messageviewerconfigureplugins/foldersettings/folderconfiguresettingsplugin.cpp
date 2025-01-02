/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsplugin.h"
#include "folderconfiguresettingsdialog.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(FolderConfigureSettingsPlugin, "messageviewer_folderconfiguresettingsplugin.json")

FolderConfigureSettingsPlugin::FolderConfigureSettingsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

FolderConfigureSettingsPlugin::~FolderConfigureSettingsPlugin() = default;

void FolderConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    FolderConfigureSettingsDialog dlg(parent);
    dlg.exec();
}

#include "folderconfiguresettingsplugin.moc"

#include "moc_folderconfiguresettingsplugin.cpp"
