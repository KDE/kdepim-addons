/*
    Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "webdavplugin.h"
#include <kpluginfactory.h>
#include <KLocalizedString>
#include <QUrl>
#include <QIcon>

using namespace PimCommon;
K_PLUGIN_FACTORY_WITH_JSON(PimCommonWebDavPluginFactory, "pimcommon_webdavplugin.json", registerPlugin<WebDavPlugin>();)

WebDavPlugin::WebDavPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::StorageServicePlugin(parent)
{

}

WebDavPlugin::~WebDavPlugin()
{

}

QString WebDavPlugin::storageServiceName() const
{
    return QStringLiteral("webdav");
}

StorageServicePlugin::Capabilities WebDavPlugin::capabilities() const
{
    StorageServicePlugin::Capabilities cap;
    cap |= AccountInfoCapability;
    cap |= UploadFileCapability;
    cap |= DownloadFileCapability;
    cap |= CreateFolderCapability;
    cap |= DeleteFolderCapability;
    cap |= ListFolderCapability;
    //cap |= ShareLinkCapability;
    cap |= DeleteFileCapability;
    cap |= RenameFolderCapability;
    cap |= RenameFileCapabilitity;
    cap |= MoveFileCapability;
    cap |= MoveFolderCapability;
    cap |= CopyFileCapability;
    cap |= CopyFolderCapability;

    return cap;
}

QString WebDavPlugin::description() const
{
    return i18n("The WebDAV service allows access to any Web application that uses the WebDAV protocol, such as ownCloud, Kolab, and others.");
}

QUrl WebDavPlugin::serviceUrl() const
{
    return QUrl();
}

QIcon WebDavPlugin::icon() const
{
    return QIcon::fromTheme(QStringLiteral("folder-remote"));
}

PimCommon::StorageServiceInterface *WebDavPlugin::createStorageService(const QString &identifier)
{
    //TODO
    return Q_NULLPTR;
}

#include "webdavplugin.moc"
