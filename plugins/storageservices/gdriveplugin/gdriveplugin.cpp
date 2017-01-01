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

#include "gdriveplugin.h"
#include <kpluginfactory.h>
#include <KLocalizedString>
#include <QUrl>
#include <QIcon>

using namespace PimCommon;
K_PLUGIN_FACTORY_WITH_JSON(PimCommonGDrivePluginFactory, "pimcommon_gdriveplugin.json", registerPlugin<GDrivePlugin>();)

GDrivePlugin::GDrivePlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::StorageServicePlugin(parent)
{

}

GDrivePlugin::~GDrivePlugin()
{

}

QString GDrivePlugin::storageServiceName() const
{
    return QStringLiteral("googledrive");
}

QIcon GDrivePlugin::icon() const
{
    return QIcon::fromTheme(QStringLiteral("kdepim-googledrive"));
}

StorageServicePlugin::Capabilities GDrivePlugin::capabilities() const
{
    StorageServicePlugin::Capabilities cap;
    cap |= AccountInfoCapability;
    cap |= UploadFileCapability;
    //cap |= DownloadFileCapability;
    cap |= CreateFolderCapability;
    cap |= DeleteFolderCapability;
    cap |= ListFolderCapability;
    cap |= DeleteFileCapability;
    //cap |= ShareLinkCapability;
    cap |= RenameFolderCapability;
    cap |= RenameFileCapabilitity;
    //cap |= MoveFileCapability;
    //cap |= MoveFolderCapability;
    cap |= CopyFileCapability;
    //cap |= CopyFolderCapability;
    return cap;
}

QString GDrivePlugin::description() const
{
    return i18n("Googledrive is a file hosting that offers cloud storage, file synchronization, and client software.");
}

QUrl GDrivePlugin::serviceUrl() const
{
    return QUrl(QStringLiteral("http://www.google.com/drive"));
}

PimCommon::StorageServiceInterface *GDrivePlugin::createStorageService(const QString &identifier)
{
    //TODO
    return Q_NULLPTR;
}

#include "gdriveplugin.moc"
