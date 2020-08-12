/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapimportexportplugin.h"
#include "ldapimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(LDapImportExportPlugin, "kaddressbook_importexportldapplugin.json")

LDapImportExportPlugin::LDapImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::KAddressBookImportExportPlugin(parent)
{
}

LDapImportExportPlugin::~LDapImportExportPlugin()
{
}

PimCommon::AbstractGenericPluginInterface *LDapImportExportPlugin::createInterface(QObject *parent)
{
    LDapImportExportPluginInterface *interface = new LDapImportExportPluginInterface(parent);
    return interface;
}

bool LDapImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "ldapimportexportplugin.moc"
