/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "windowscontactimportexportplugin.h"
#include "windowscontactimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(WindowsContactImportExportPlugin, "kaddressbook_importexportwindowscontactplugin.json")

WindowsContactImportExportPlugin::WindowsContactImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::KAddressBookImportExportPlugin(parent)
{
}

WindowsContactImportExportPlugin::~WindowsContactImportExportPlugin()
{
}

PimCommon::AbstractGenericPluginInterface *WindowsContactImportExportPlugin::createInterface(QObject *parent)
{
    WindowsContactImportExportPluginInterface *interface = new WindowsContactImportExportPluginInterface(parent);
    return interface;
}

bool WindowsContactImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "windowscontactimportexportplugin.moc"
