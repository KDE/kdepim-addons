/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigplugin.h"
#include "openurlwithconfiguredialog.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(OpenUrlWithConfigPlugin, "messageviewer_openurlwithconfigplugin.json")

OpenUrlWithConfigPlugin::OpenUrlWithConfigPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerConfigureSettingsPlugin(parent)
{
}

OpenUrlWithConfigPlugin::~OpenUrlWithConfigPlugin() = default;

void OpenUrlWithConfigPlugin::showConfigureDialog(QWidget *parent)
{
    OpenUrlWithConfigureDialog dlg(parent);
    dlg.exec();
}

#include "openurlwithconfigplugin.moc"

#include "moc_openurlwithconfigplugin.cpp"
