/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "csvimportexportplugin.h"
#include "csvimportexportplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CSVImportExportPlugin, "kaddressbook_importexportcsvplugin.json")

CSVImportExportPlugin::CSVImportExportPlugin(QObject *parent, const QList<QVariant> &)
    : KAddressBookImportExport::Plugin(parent)
{
}

CSVImportExportPlugin::~CSVImportExportPlugin() = default;

PimCommon::AbstractGenericPluginInterface *CSVImportExportPlugin::createInterface(QObject *parent)
{
    return new CSVImportExportPluginInterface(parent);
}

bool CSVImportExportPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "csvimportexportplugin.moc"

#include "moc_csvimportexportplugin.cpp"
