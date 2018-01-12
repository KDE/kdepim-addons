/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2018 Laurent Montel <laurent.montel@kdab.com>

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

#include "addressgrantleeobject.h"
#include "iconnamecache_p.h"
#include <KIconLoader>
#include <KLocalizedString>
#include <QUrlQuery>

AddressGrantleeObject::AddressGrantleeObject(const KContacts::Address &address, int addressIndex, QObject *parent)
    : QObject(parent)
    , mAddress(address)
    , mAddressIndex(addressIndex)
{
    mIconSize = KIconLoader::global()->currentSize(KIconLoader::Small);
}

AddressGrantleeObject::~AddressGrantleeObject()
{
}

QString AddressGrantleeObject::formattedAddress() const
{
    QString str;
    if (mAddress.label().isEmpty()) {
        str = mAddress.formattedAddress().trimmed().toHtmlEscaped();
    } else {
        str = mAddress.label().toHtmlEscaped();
    }
    return str;
}

QString AddressGrantleeObject::createActionUrl(const QString &actionName) const
{
    QUrl url;
    url.setScheme(QStringLiteral("addresslocationaction"));
    url.setPath(actionName);
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("id"), QString::number(mAddressIndex));
    url.setQuery(query);
    return url.toDisplayString();
}

QString AddressGrantleeObject::preferredAddressAction() const
{
    QString text;
    if (preferredAddress()) {
        const QString iconPath = QUrl::fromLocalFile(IconNameCache::instance()->iconPath(QStringLiteral("bookmarks"), KIconLoader::Small)).url();
        text = QStringLiteral("<img class=\"headimage\"  height=\"%3\" width=\"%3\" title=\"%1\" src=\"%2\"></a>\n")
               .arg(i18n("Remove Address"), iconPath, QString::number(mIconSize));
    }
    return text;
}

QString AddressGrantleeObject::postOfficeBox() const
{
    return mAddress.postOfficeBox();
}

QString AddressGrantleeObject::street() const
{
    return mAddress.street();
}

QString AddressGrantleeObject::locality() const
{
    return mAddress.locality();
}

QString AddressGrantleeObject::region() const
{
    return mAddress.region();
}

QString AddressGrantleeObject::postalCode() const
{
    return mAddress.postalCode();
}

QString AddressGrantleeObject::country() const
{
    return mAddress.country();
}

QString AddressGrantleeObject::removeAddressAction() const
{
    const QString iconPath = QUrl::fromLocalFile(IconNameCache::instance()->iconPath(QStringLiteral("edit-delete"), KIconLoader::Small)).url();
    const QString text = QStringLiteral("<a href=\"%1\"><img class=\"headimage\" height=\"%4\" width=\"%4\" title=\"%3\" src=\"%2\"></a>\n")
                         .arg(createActionUrl(QStringLiteral("removeaddress")), iconPath, i18n("Remove Address"), QString::number(mIconSize));
    return text;
}

QString AddressGrantleeObject::modifyAddressAction() const
{
    const QString iconPath = QUrl::fromLocalFile(IconNameCache::instance()->iconPath(QStringLiteral("document-edit"), KIconLoader::Small)).url();
    const QString text = QStringLiteral("<a href=\"%1\"><img class=\"headimage\" height=\"%4\" width=\"%4\" title=\"%3\" src=\"%2\"></a>\n")
                         .arg(createActionUrl(QStringLiteral("editaddress")), iconPath, i18n("Edit Address"), QString::number(mIconSize));
    return text;
}

QString AddressGrantleeObject::addressType() const
{
    return KContacts::Address::typeLabel(mAddress.type());
}

bool AddressGrantleeObject::preferredAddress() const
{
    return mAddress.type() & KContacts::Address::Pref;
}
