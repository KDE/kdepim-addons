/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingsplugin.h"
#include "gravatarconfiguresettingsplugindialog.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(GravatarConfigureSettingsPlugin, "messageviewer_gravatarconfigplugin.json")

GravatarConfigureSettingsPlugin::GravatarConfigureSettingsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

GravatarConfigureSettingsPlugin::~GravatarConfigureSettingsPlugin() = default;

void GravatarConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    GravatarConfigureSettingsPluginDialog dlg(parent);
    dlg.exec();
}

#include "gravatarconfiguresettingsplugin.moc"

#include "moc_gravatarconfiguresettingsplugin.cpp"
