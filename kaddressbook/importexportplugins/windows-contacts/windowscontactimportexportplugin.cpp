/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "windowscontactimportexportplugin.h"
#include "windowscontactimportexportplugininterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(WindowsContactImportExportPlugin, "kaddressbook_importexportwindowscontactplugin.json")

WindowsContactImportExportPlugin::WindowsContactImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::Plugin(parent)
{
}

WindowsContactImportExportPlugin::~WindowsContactImportExportPlugin() = default;

PimCommon::AbstractGenericPluginInterface *WindowsContactImportExportPlugin::createInterface(QObject *parent)
{
    return new WindowsContactImportExportPluginInterface(parent);
}

bool WindowsContactImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "windowscontactimportexportplugin.moc"

#include "moc_windowscontactimportexportplugin.cpp"
