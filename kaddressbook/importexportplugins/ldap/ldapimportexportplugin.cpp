/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

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
    auto interface = new LDapImportExportPluginInterface(parent);
    return interface;
}

bool LDapImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "ldapimportexportplugin.moc"
