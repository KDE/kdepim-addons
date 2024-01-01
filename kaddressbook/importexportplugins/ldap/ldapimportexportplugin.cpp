/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapimportexportplugin.h"
#include "ldapimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(LDapImportExportPlugin, "kaddressbook_importexportldapplugin.json")

LDapImportExportPlugin::LDapImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::Plugin(parent)
{
}

LDapImportExportPlugin::~LDapImportExportPlugin() = default;

PimCommon::AbstractGenericPluginInterface *LDapImportExportPlugin::createInterface(QObject *parent)
{
    return new LDapImportExportPluginInterface(parent);
}

bool LDapImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "ldapimportexportplugin.moc"

#include "moc_ldapimportexportplugin.cpp"
