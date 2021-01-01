/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "dkimconfiguresettingsplugin.h"
#include "dkimconfiguredialog.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(DkimConfigureSettingsPlugin, "messageviewer_dkimconfigplugin.json")

DkimConfigureSettingsPlugin::DkimConfigureSettingsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

DkimConfigureSettingsPlugin::~DkimConfigureSettingsPlugin()
{
}

void DkimConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<DKIMConfigureDialog> dlg = new DKIMConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "dkimconfiguresettingsplugin.moc"
