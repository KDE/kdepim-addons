/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "vcardimportexportplugin.h"
#include "vcardimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(VCardImportExportPlugin, "kaddressbook_importexportvcardplugin.json")
VCardImportExportPlugin::VCardImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::Plugin(parent)
{
}

VCardImportExportPlugin::~VCardImportExportPlugin() = default;

PimCommon::AbstractGenericPluginInterface *VCardImportExportPlugin::createInterface(QObject *parent)
{
    return new VCardImportExportPluginInterface(parent);
}

bool VCardImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "vcardimportexportplugin.moc"

#include "moc_vcardimportexportplugin.cpp"
