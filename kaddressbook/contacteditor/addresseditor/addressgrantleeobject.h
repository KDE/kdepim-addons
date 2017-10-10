/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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

#ifndef ADDRESSGRANTLEEOBJECT_H
#define ADDRESSGRANTLEEOBJECT_H

#include <QObject>
#include <KContacts/Address>

class AddressGrantleeObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString removeAddressAction READ removeAddressAction)
    Q_PROPERTY(QString modifyAddressAction READ modifyAddressAction)
    Q_PROPERTY(QString formattedAddress READ formattedAddress)
    Q_PROPERTY(QString preferredAddressAction READ preferredAddressAction)
    Q_PROPERTY(QString addressType READ addressType)
    Q_PROPERTY(QString postOfficeBox READ postOfficeBox)
    Q_PROPERTY(QString street READ street)
    Q_PROPERTY(QString locality READ locality)
    Q_PROPERTY(QString region READ region)
    Q_PROPERTY(QString postalCode READ postalCode)
    Q_PROPERTY(QString country READ country)
    Q_PROPERTY(bool preferredAddress READ preferredAddress)
public:
    explicit AddressGrantleeObject(const KContacts::Address &address, int addressIndex, QObject *parent = nullptr);
    ~AddressGrantleeObject();

    QString removeAddressAction() const;
    QString modifyAddressAction() const;
    QString formattedAddress() const;
    QString addressType() const;
    bool preferredAddress() const;
    QString preferredAddressAction() const;
    QString postOfficeBox() const;
    QString street() const;
    QString locality() const;
    QString region() const;
    QString postalCode() const;
    QString country() const;

private:
    QString createActionUrl(const QString &actionName) const;
    KContacts::Address mAddress;
    int mAddressIndex;
    int mIconSize;
};
#endif // ADDRESSGRANTLEEOBJECT_H
