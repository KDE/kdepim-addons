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

#include "importwindowcontact.h"
#include "importexportwindowscontactplugin_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QDomDocument>
#include <QFile>

ImportWindowContact::ImportWindowContact()
{

}

ImportWindowContact::~ImportWindowContact()
{

}

KContacts::Addressee::List ImportWindowContact::importFile(const QString &fileName)
{
    KContacts::Addressee::List lst;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        if (!mAutoTest) {
            const QString msg = i18n("<qt>Unable to open <b>%1</b> for reading.</qt>", fileName);
            KMessageBox::error(mParentWidget, msg);
        } else {
            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "Impossible to open file: " << fileName;
        }
        return lst;
    }
    QDomDocument doc;
    if (loadDomElement(doc, &file)) {
        QDomElement list = doc.documentElement();
        if (list.isNull()) {
            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "No list defined in file";
        } else {
            KContacts::Addressee contact;
            if (mAutoTest) {
                contact.setUid(QStringLiteral("foo"));
            }
            for (QDomElement e = list.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
                const QString tag = e.tagName();
                if (tag == QLatin1String("c:EmailAddressCollection")) {
                    KContacts::Email::List lstEmails;
                    for (QDomElement emails = e.firstChildElement(); !emails.isNull(); emails = emails.nextSiblingElement()) {
                        const QString emailsTag = emails.tagName();
                        qDebug() << " emailstag "<< emailsTag;
                        if (emailsTag == QLatin1String("c:EmailAddress")) {
                            KContacts::Email email;
                            for (QDomElement addresses = emails.firstChildElement(); !addresses.isNull(); addresses = addresses.nextSiblingElement()) {
                                const QString addressesTag = addresses.tagName();
                                if (addressesTag == QLatin1String("c:Type")) {

                                } else if (addressesTag == QLatin1String("c:Address")) {
                                    email.setEmail(addresses.text());
                                } else {
                                    qDebug() << " address tag not supported yet " << addressesTag;
                                }
                            }
                            lstEmails << email;
                        }
                        contact.setEmailList(lstEmails);
                    }
                } else if (tag == QLatin1String("c:NameCollection")) {
                    for (QDomElement name = e.firstChildElement(); !name.isNull(); name = name.nextSiblingElement()) {
                        const QString nameTag = name.tagName();
                        if (nameTag == QLatin1String("c:Name")) {
                            for (QDomElement nameInfo = name.firstChildElement(); !nameInfo.isNull(); nameInfo = nameInfo.nextSiblingElement()) {
                                const QString nameInfoTag = nameInfo.tagName();
                                if (nameInfoTag == QLatin1String("c:FormattedName")) {
                                    contact.setName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1String("c:GivenName")) {
                                    contact.setGivenName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1String("c:FamilyName")) {
                                    contact.setFamilyName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1String("c:FormattedName")) {
                                    contact.setFormattedName(nameInfo.text());
                                } else {
                                    qDebug() << " name tag not supported yet " << nameInfoTag;
                                }
                            }
                        } else {
                            qDebug() << " name tag unknow:" << nameTag;
                        }
                    }
                } else if (tag == QLatin1String("c:PhotoCollection")) {

                } else {
                    qDebug() << "unknown tag " << tag;
                }
            }
            lst << contact;
        }
    }
    return lst;
}

bool ImportWindowContact::loadDomElement(QDomDocument &doc, QFile *file)
{
    QString errorMsg;
    int errorRow;
    int errorCol;
    if (!doc.setContent(file, &errorMsg, &errorRow, &errorCol)) {
        qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "Unable to load document.Parse error in line " << errorRow
                               << ", col " << errorCol << ": " << errorMsg;
        return false;
    }
    return true;
}

void ImportWindowContact::setParentWidget(QWidget *parentWidget)
{
    mParentWidget = parentWidget;
}

void ImportWindowContact::setAutoTests(bool b)
{
    mAutoTest = b;
}
