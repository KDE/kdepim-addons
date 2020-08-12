/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "vcardimportexportplugin.h"
#include "vcardimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(VCardImportExportPlugin, "kaddressbook_importexportvcardplugin.json")
VCardImportExportPlugin::VCardImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::KAddressBookImportExportPlugin(parent)
{
}

VCardImportExportPlugin::~VCardImportExportPlugin()
{
}

PimCommon::AbstractGenericPluginInterface *VCardImportExportPlugin::createInterface(QObject *parent)
{
    VCardImportExportPluginInterface *interface = new VCardImportExportPluginInterface(parent);
    return interface;
}

bool VCardImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "vcardimportexportplugin.moc"
