/*
    Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "hubicplugin.h"
#include <kpluginfactory.h>
#include <KLocalizedString>
#include <QUrl>

using namespace PimCommon;
K_PLUGIN_FACTORY_WITH_JSON(PimCommonHubicPluginFactory, "pimcommon_hubicplugin.json", registerPlugin<HubicPlugin>();)

HubicPlugin::HubicPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::StorageServicePlugin(parent)
{

}

HubicPlugin::~HubicPlugin()
{

}

QString HubicPlugin::hubicClientId() const
{
    //TODO
    return QString();
}

QString HubicPlugin::hubicClientSecret() const
{
    //TODO
    return QString();
}

QString HubicPlugin::oauth2RedirectUrl() const
{
    //TODO
    return QString();
}

QString HubicPlugin::storageServiceName() const
{
    return QStringLiteral("hubic");
}

StorageServicePlugin::Capabilities HubicPlugin::capabilities() const
{
    StorageServicePlugin::Capabilities cap;
#if 0 //Disable for the moment
    cap |= AccountInfoCapability;
    //cap |= UploadFileCapability;
    //cap |= DownloadFileCapability;
    cap |= CreateFolderCapability;
    cap |= DeleteFolderCapability;
    cap |= ListFolderCapability;
    //cap |= ShareLinkCapability;
    cap |= DeleteFileCapability;
    //cap |= RenameFolderCapability;
    //cap |= RenameFileCapabilitity;
    //cap |= MoveFileCapability;
    //cap |= MoveFolderCapability;
    //cap |= CopyFileCapability;
    //cap |= CopyFolderCapability;
#endif

    return cap;
}

QString HubicPlugin::description() const
{
    return i18n("Hubic is a file hosting service operated by Ovh, Inc. that offers cloud storage, file synchronization, and client software.");
}

QUrl HubicPlugin::serviceUrl() const
{
    return QUrl(QStringLiteral("https://hubic.com"));
}

PimCommon::StorageServiceInterface *HubicPlugin::createStorageService(const QString &identifier)
{
    //TODO
    return Q_NULLPTR;
}

#include "hubicplugin.moc"
