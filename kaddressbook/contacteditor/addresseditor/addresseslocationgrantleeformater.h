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

#ifndef ADDRESSESLOCATIONGRANTLEEFORMATER_H
#define ADDRESSESLOCATIONGRANTLEEFORMATER_H

#include <QObject>

#include <KContacts/Address>
#include <QSharedPointer>
#include <grantlee/templateloader.h>
namespace Grantlee {
class Engine;
}
class AddressesLocationGrantleeFormater : public QObject
{
    Q_OBJECT
public:
    explicit AddressesLocationGrantleeFormater(QObject *parent = nullptr);
    ~AddressesLocationGrantleeFormater();

    QString formatAddresses(const KContacts::Address::List &addresses);
    void setReadOnly(bool readOnly);
private:
    void changeGrantleePath(const QString &path);
    Grantlee::Engine *mEngine = nullptr;
    QString mErrorMessage;
    QString mGrantleeThemePath;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mSelfcontainedTemplate;
    bool mReadOnly;
};
#endif // ADDRESSESLOCATIONGRANTLEEFORMATER_H
