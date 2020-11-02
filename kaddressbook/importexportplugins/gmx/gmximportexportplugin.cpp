/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gmximportexportplugin.h"
#include "gmximportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(GMXImportExportPlugin, "kaddressbook_importexportgmxplugin.json")

GMXImportExportPlugin::GMXImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::Plugin(parent)
{
}

GMXImportExportPlugin::~GMXImportExportPlugin() = default;

PimCommon::AbstractGenericPluginInterface *GMXImportExportPlugin::createInterface(QObject *parent)
{
    auto *interface = new GMXImportExportPluginInterface(parent);
    return interface;
}

bool GMXImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "gmximportexportplugin.moc"
