/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

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

GravatarConfigureSettingsPlugin::~GravatarConfigureSettingsPlugin()
{
}

void GravatarConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<GravatarConfigureSettingsPluginDialog> dlg = new GravatarConfigureSettingsPluginDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "gravatarconfiguresettingsplugin.moc"
