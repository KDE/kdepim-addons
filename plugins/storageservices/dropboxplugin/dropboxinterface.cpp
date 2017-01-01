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

#include "dropboxinterface.h"

using namespace PimCommon;

DropBoxInterface::DropBoxInterface(DropBoxPlugin *plugin, QObject *parent)
    : PimCommon::StorageServiceInterface(parent),
      mPlugin(plugin)
{

}

DropBoxInterface::~DropBoxInterface()
{

}

void DropBoxInterface::shutdownService()
{

}

bool DropBoxInterface::isConfigurated() const
{
    //TODO
    return true;
}

void DropBoxInterface::downloadFile(const QString &name, const QString &fileId, const QString &destination)
{

}

void DropBoxInterface::uploadFile(const QString &filename, const QString &uploadAsName, const QString &destination)
{

}

void DropBoxInterface::accountInfo()
{

}

void DropBoxInterface::createFolder(const QString &foldername, const QString &destination)
{

}

void DropBoxInterface::listFolder(const QString &folder)
{

}

void DropBoxInterface::authentication()
{

}

void DropBoxInterface::shareLink(const QString &root, const QString &path)
{

}

void DropBoxInterface::createServiceFolder()
{

}

void DropBoxInterface::deleteFile(const QString &filename)
{

}

void DropBoxInterface::deleteFolder(const QString &foldername)
{

}

void DropBoxInterface::renameFolder(const QString &source, const QString &destination)
{

}

void DropBoxInterface::renameFile(const QString &source, const QString &destination)
{

}

void DropBoxInterface::moveFile(const QString &source, const QString &destination)
{

}

void DropBoxInterface::moveFolder(const QString &source, const QString &destination)
{

}

void DropBoxInterface::copyFile(const QString &source, const QString &destination)
{

}

void DropBoxInterface::copyFolder(const QString &source, const QString &destination)
{

}

void DropBoxInterface::removeConfig()
{

}
