/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2019 Laurent Montel <laurent.montel@kdab.com>

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

#include "addresseslocationgrantleeformater.h"
#include "addressgrantleeobject.h"
#include <grantlee/engine.h>
#include <QVariantList>
#include <QStandardPaths>

AddressesLocationGrantleeFormater::AddressesLocationGrantleeFormater(QObject *parent)
    : QObject(parent)
    , mEngine(new Grantlee::Engine)
    , mReadOnly(false)
{
    mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
    mGrantleeThemePath = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                                QStringLiteral("contacteditor/grantleetheme/default/"),
                                                QStandardPaths::LocateDirectory);
    changeGrantleePath(mGrantleeThemePath);
}

AddressesLocationGrantleeFormater::~AddressesLocationGrantleeFormater()
{
    delete mEngine;
    mTemplateLoader.clear();
}

QString AddressesLocationGrantleeFormater::formatAddresses(const KContacts::Address::List &addresses)
{
    QVariantList addressList;
    const int nbAddress(addresses.count());
    addressList.reserve(nbAddress);
    QList<AddressGrantleeObject *> lstAddress;
    lstAddress.reserve(nbAddress);
    for (int i = 0; i < nbAddress; ++i) {
        AddressGrantleeObject *addressObj = new AddressGrantleeObject(addresses.at(i), i);
        addressList << QVariant::fromValue(static_cast<QObject *>(addressObj));
        lstAddress.append(addressObj);
    }
    QVariantHash addressHash;
    addressHash.insert(QStringLiteral("addresses"), addressList);
    addressHash.insert(QStringLiteral("absoluteThemePath"), mGrantleeThemePath);
    addressHash.insert(QStringLiteral("readOnly"), mReadOnly);

    Grantlee::Context context(addressHash);
    const QString contentHtml = mSelfcontainedTemplate->render(&context);
    qDeleteAll(lstAddress);
    return contentHtml;
}

void AddressesLocationGrantleeFormater::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;
}

void AddressesLocationGrantleeFormater::changeGrantleePath(const QString &path)
{
    if (!mTemplateLoader) {
        mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
    }
    mTemplateLoader->setTemplateDirs(QStringList() << path);
    mEngine->addTemplateLoader(mTemplateLoader);

    mSelfcontainedTemplate = mEngine->loadByName(QStringLiteral("addresseslocation.html"));
    if (mSelfcontainedTemplate->error()) {
        mErrorMessage += mSelfcontainedTemplate->errorString() + QLatin1String("<br>");
    }
}
