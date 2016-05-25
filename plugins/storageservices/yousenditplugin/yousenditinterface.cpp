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

#include "yousenditinterface.h"

using namespace PimCommon;

YouSendItInterface::YouSendItInterface(YouSendItPlugin *plugin, QObject *parent)
    : PimCommon::StorageServiceInterface(parent),
      mPlugin(plugin)
{

}

YouSendItInterface::~YouSendItInterface()
{

}

void YouSendItInterface::downloadFile(const QString &name, const QString &fileId, const QString &destination)
{

}

void YouSendItInterface::uploadFile(const QString &filename, const QString &uploadAsName, const QString &destination)
{

}

void YouSendItInterface::accountInfo()
{

}

void YouSendItInterface::createFolder(const QString &foldername, const QString &destination)
{

}

void YouSendItInterface::listFolder(const QString &folder)
{

}

void YouSendItInterface::authentication()
{

}

void YouSendItInterface::shareLink(const QString &root, const QString &path)
{

}

void YouSendItInterface::createServiceFolder()
{

}

void YouSendItInterface::deleteFile(const QString &filename)
{

}

void YouSendItInterface::deleteFolder(const QString &foldername)
{

}

void YouSendItInterface::renameFolder(const QString &source, const QString &destination)
{

}

void YouSendItInterface::renameFile(const QString &source, const QString &destination)
{

}

void YouSendItInterface::moveFile(const QString &source, const QString &destination)
{

}

void YouSendItInterface::moveFolder(const QString &source, const QString &destination)
{

}

void YouSendItInterface::copyFile(const QString &source, const QString &destination)
{

}

void YouSendItInterface::copyFolder(const QString &source, const QString &destination)
{

}

void YouSendItInterface::shutdownService()
{

}

void YouSendItInterface::removeConfig()
{

}

bool YouSendItInterface::isConfigurated() const
{
    //TODO
    return true;
}
