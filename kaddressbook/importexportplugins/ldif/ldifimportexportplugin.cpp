/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldifimportexportplugin.h"
#include "ldifimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(LDifImportExportPlugin, "kaddressbook_importexportldifplugin.json")

LDifImportExportPlugin::LDifImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::KAddressBookImportExportPlugin(parent)
{
}

LDifImportExportPlugin::~LDifImportExportPlugin()
{
}

PimCommon::AbstractGenericPluginInterface *LDifImportExportPlugin::createInterface(QObject *parent)
{
    LDifImportExportPluginInterface *interface = new LDifImportExportPluginInterface(parent);
    return interface;
}

bool LDifImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "ldifimportexportplugin.moc"
