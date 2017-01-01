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

#include "webdavinterface.h"

using namespace PimCommon;

WebDavInterface::WebDavInterface(WebDavPlugin *plugin, QObject *parent)
    : PimCommon::StorageServiceInterface(parent),
      mPlugin(plugin)
{

}

WebDavInterface::~WebDavInterface()
{

}

void WebDavInterface::shutdownService()
{

}

bool WebDavInterface::isConfigurated() const
{
    //TODO
    return true;
}

void WebDavInterface::downloadFile(const QString &name, const QString &fileId, const QString &destination)
{

}

void WebDavInterface::uploadFile(const QString &filename, const QString &uploadAsName, const QString &destination)
{

}

void WebDavInterface::accountInfo()
{

}

void WebDavInterface::createFolder(const QString &foldername, const QString &destination)
{

}

void WebDavInterface::listFolder(const QString &folder)
{

}

void WebDavInterface::authentication()
{

}

void WebDavInterface::shareLink(const QString &root, const QString &path)
{

}

void WebDavInterface::createServiceFolder()
{

}

void WebDavInterface::deleteFile(const QString &filename)
{

}

void WebDavInterface::deleteFolder(const QString &foldername)
{

}

void WebDavInterface::renameFolder(const QString &source, const QString &destination)
{

}

void WebDavInterface::renameFile(const QString &source, const QString &destination)
{

}

void WebDavInterface::moveFile(const QString &source, const QString &destination)
{

}

void WebDavInterface::moveFolder(const QString &source, const QString &destination)
{

}

void WebDavInterface::copyFile(const QString &source, const QString &destination)
{

}

void WebDavInterface::copyFolder(const QString &source, const QString &destination)
{

}

void WebDavInterface::removeConfig()
{

}
