/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
