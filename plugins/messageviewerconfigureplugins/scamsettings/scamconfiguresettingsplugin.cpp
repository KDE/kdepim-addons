/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingsplugin.h"
#include "scamconfiguresettingsdialog.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ScamConfigureSettingsPlugin, "messageviewer_scamconfiguresettingsplugin.json")

ScamConfigureSettingsPlugin::ScamConfigureSettingsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

ScamConfigureSettingsPlugin::~ScamConfigureSettingsPlugin() = default;

void ScamConfigureSettingsPlugin::showConfigureDialog(QWidget *parent)
{
    ScamConfigureSettingsDialog dlg(parent);
    dlg.exec();
}

#include "scamconfiguresettingsplugin.moc"

#include "moc_scamconfiguresettingsplugin.cpp"
