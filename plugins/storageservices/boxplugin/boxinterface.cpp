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

#include "boxinterface.h"

using namespace PimCommon;

BoxInterface::BoxInterface(BoxPlugin *plugin, QObject *parent)
    : PimCommon::StorageServiceInterface(parent),
      mPlugin(plugin)
{

}

BoxInterface::~BoxInterface()
{

}

void BoxInterface::shutdownService()
{

}

bool BoxInterface::isConfigurated() const
{
    //TODO
    return true;
}

void BoxInterface::downloadFile(const QString &name, const QString &fileId, const QString &destination)
{

}

void BoxInterface::uploadFile(const QString &filename, const QString &uploadAsName, const QString &destination)
{

}

void BoxInterface::accountInfo()
{

}

void BoxInterface::createFolder(const QString &foldername, const QString &destination)
{

}

void BoxInterface::listFolder(const QString &folder)
{

}

void BoxInterface::authentication()
{

}

void BoxInterface::shareLink(const QString &root, const QString &path)
{

}

void BoxInterface::createServiceFolder()
{

}

void BoxInterface::deleteFile(const QString &filename)
{

}

void BoxInterface::deleteFolder(const QString &foldername)
{

}

void BoxInterface::renameFolder(const QString &source, const QString &destination)
{

}

void BoxInterface::renameFile(const QString &source, const QString &destination)
{

}

void BoxInterface::moveFile(const QString &source, const QString &destination)
{

}

void BoxInterface::moveFolder(const QString &source, const QString &destination)
{

}

void BoxInterface::copyFile(const QString &source, const QString &destination)
{

}

void BoxInterface::copyFolder(const QString &source, const QString &destination)
{

}

void BoxInterface::removeConfig()
{

}
