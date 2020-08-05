/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "importwindowcontacttest.h"
#include "../importwindowcontact.h"
#include <QTest>
#include <KContacts/Addressee>
QTEST_MAIN(ImportWindowContactTest)
ImportWindowContactTest::ImportWindowContactTest(QObject *parent)
    : QObject(parent)
{
}

void ImportWindowContactTest::shouldImportWindowContact_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<KContacts::Addressee::List>("result");
    QTest::newRow("empty") << QString() << KContacts::Addressee::List();
    {
        KContacts::Addressee::List result;
        KContacts::Addressee address;
        address.setName(QStringLiteral("John Doe"));
        address.setUid(QStringLiteral("foo"));
        KContacts::Email email;
        email.setEmail(QStringLiteral("sample-email@kde.org"));
        address.setEmailList({email});

        result << address;

        QTest::newRow("test1") << QStringLiteral("test1.contact") << result;
    }
    {
        KContacts::Addressee::List result;
        KContacts::Addressee address;
        address.setName(QStringLiteral("John Anon"));
        address.setFamilyName(QStringLiteral("Anon"));
        address.setGivenName(QStringLiteral("John"));
        address.setUid(QStringLiteral("foo"));
        KContacts::Email email;
        email.setEmail(QStringLiteral("sampleaddress@yahoo.com"));
        address.setEmailList({email});

        result << address;

        QTest::newRow("sample2") << QStringLiteral("sample2.contact") << result;
    }
}

void ImportWindowContactTest::shouldImportWindowContact()
{
    QFETCH(QString, filename);
    QFETCH(KContacts::Addressee::List, result);
    ImportWindowContact contact;
    contact.setAutoTests(true);
    const QString fullPath = QStringLiteral(WINDOWSCONTACT_DATADIR "/data/") + filename;

    const KContacts::Addressee::List importData = contact.importFile(fullPath);
    const bool contactEqual = (importData == result);
    //Pb with setUid which is different.
    if (!contactEqual) {
        qDebug() << " RESULT";
        for (const KContacts::Addressee &address : importData) {
            qDebug() << "Data: " << address.toString();

        }
        qDebug() << " EXPECTED";
        for (const KContacts::Addressee &address : result) {
            qDebug() << "Data: " << address.toString();
        }
    }
    QVERIFY(contactEqual);
}
