/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importwindowcontact.h"
#include "importexportwindowscontactplugin_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QDomDocument>
#include <QFile>
using namespace Qt::Literals::StringLiterals;

// https://docs.microsoft.com/en-us/previous-versions//ms735869(v=vs.85)

ImportWindowContact::ImportWindowContact() = default;

ImportWindowContact::~ImportWindowContact() = default;

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
                contact.setUid(u"foo"_s);
            }
            for (QDomElement e = list.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
                const QString tag = e.tagName();
                if (tag == "c:EmailAddressCollection"_L1) {
                    KContacts::Email::List lstEmails;
                    for (QDomElement emails = e.firstChildElement(); !emails.isNull(); emails = emails.nextSiblingElement()) {
                        const QString emailsTag = emails.tagName();
                        if (emailsTag == "c:EmailAddress"_L1) {
                            KContacts::Email email;
                            for (QDomElement addresses = emails.firstChildElement(); !addresses.isNull(); addresses = addresses.nextSiblingElement()) {
                                const QString addressesTag = addresses.tagName();
                                if (addressesTag == "c:Type"_L1) {
                                } else if (addressesTag == "c:Address"_L1) {
                                    email.setEmail(addresses.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " address tag not supported yet " << addressesTag;
                                }
                            }
                            if (email.isValid()) {
                                lstEmails << email;
                            }
                        }
                        contact.setEmailList(lstEmails);
                    }
                } else if (tag == "c:NameCollection"_L1) {
                    for (QDomElement name = e.firstChildElement(); !name.isNull(); name = name.nextSiblingElement()) {
                        const QString nameTag = name.tagName();
                        if (nameTag == "c:Name"_L1) {
                            for (QDomElement nameInfo = name.firstChildElement(); !nameInfo.isNull(); nameInfo = nameInfo.nextSiblingElement()) {
                                const QString nameInfoTag = nameInfo.tagName();
                                if (nameInfoTag == "c:FormattedName"_L1) {
                                    contact.setName(nameInfo.text());
                                } else if (nameInfoTag == "c:GivenName"_L1) {
                                    contact.setGivenName(nameInfo.text());
                                } else if (nameInfoTag == "c:FamilyName"_L1) {
                                    contact.setFamilyName(nameInfo.text());
                                } else if (nameInfoTag == "c:FormattedName"_L1) {
                                    contact.setFormattedName(nameInfo.text());
                                } else if (nameInfoTag == "c:Title"_L1) {
                                    contact.setTitle(nameInfo.text());
                                } else if (nameInfoTag == "c:NickName"_L1) {
                                    contact.setNickName(nameInfo.text());
                                } else if (nameInfoTag == "c:Prefix"_L1) {
                                    contact.setPrefix(nameInfo.text());
                                } else if (nameInfoTag == "c:Suffix"_L1) {
                                    contact.setSuffix(nameInfo.text());
                                } else {
                                    // TODO middlename/generation
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " name tag not supported yet " << nameInfoTag;
                                }
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " name tag unknown:" << nameTag;
                        }
                    }
                } else if (tag == "c:PhoneNumberCollection"_L1) {
                    for (QDomElement number = e.firstChildElement(); !number.isNull(); number = number.nextSiblingElement()) {
                        const QString numberTag = number.tagName();
                        if (numberTag == "c:PhoneNumber"_L1) {
                            KContacts::PhoneNumber phoneNumber;
                            for (QDomElement numberInfo = number.firstChildElement(); !numberInfo.isNull(); numberInfo = numberInfo.nextSiblingElement()) {
                                const QString numberInfoTag = numberInfo.tagName();
                                if (numberInfoTag == "c:Number"_L1) {
                                    phoneNumber.setNumber(numberInfo.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " number info tag not supported yet:" << numberInfoTag;
                                }
                            }
                            if (!phoneNumber.isEmpty()) {
                                contact.insertPhoneNumber(phoneNumber);
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " number tag unknown:" << numberTag;
                        }
                    }
                } else if (tag == "c:IMAddressCollection"_L1) {
                    for (QDomElement im = e.firstChildElement(); !im.isNull(); im = im.nextSiblingElement()) {
                        const QString imTag = im.tagName();
                        if (imTag == "c:IMAddress"_L1) {
                            KContacts::Impp impp;
                            for (QDomElement imInfo = im.firstChildElement(); !imInfo.isNull(); imInfo = imInfo.nextSiblingElement()) {
                                const QString imInfoTag = imInfo.tagName();
                                if (imInfoTag == "c:Value"_L1) {
                                    impp.setAddress(QUrl(imInfo.text()));
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " im info tag not supported yet " << imInfoTag;
                                }
                            }
                            if (impp.isValid()) {
                                contact.insertImpp(impp);
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " im tag unknown:" << imTag;
                        }
                    }
                } else if (tag == "c:PhotoCollection"_L1) {
                    for (QDomElement photo = e.firstChildElement(); !photo.isNull(); photo = photo.nextSiblingElement()) {
                        const QString photoTag = photo.tagName();
                        if (photoTag == "c:Photo"_L1) {
                            KContacts::Picture picture;
                            for (QDomElement photoInfo = photo.firstChildElement(); !photoInfo.isNull(); photoInfo = photoInfo.nextSiblingElement()) {
                                const QString photoInfoTag = photoInfo.tagName();
                                if (photoInfoTag == "c:Value"_L1) {
                                    const QString contentType = photoInfo.attribute(u"c:ContentType"_s);
                                    picture.setRawData(photoInfo.text().toUtf8(), contentType);
                                } else if (photoInfoTag == "c:Url"_L1) {
                                    picture.setUrl(photoInfo.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " photo info tag not supported yet " << photoInfoTag;
                                }
                            }
                            if (!picture.isEmpty()) {
                                contact.setPhoto(picture);
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " photo tag unknown:" << photoTag;
                        }
                    }
                } else if (tag == "c:PhysicalAddressCollection"_L1) {
                    for (QDomElement address = e.firstChildElement(); !address.isNull(); address = address.nextSiblingElement()) {
                        const QString addressTag = address.tagName();
                        if (addressTag == "c:PhysicalAddress"_L1) {
                            KContacts::Address addressType;
                            for (QDomElement addressInfo = address.firstChildElement(); !addressInfo.isNull(); addressInfo = addressInfo.nextSiblingElement()) {
                                const QString addressInfoTag = addressInfo.tagName();
                                if (addressInfoTag == "c:AddressLabel"_L1) {
                                    addressType.setLabel(addressInfo.text());
                                } else if (addressInfoTag == "c:Street"_L1) {
                                    addressType.setStreet(addressInfo.text());
                                } else if (addressInfoTag == "c:Locality"_L1) {
                                    addressType.setLocality(addressInfo.text());
                                } else if (addressInfoTag == "c:Region"_L1) {
                                    addressType.setRegion(addressInfo.text());
                                } else if (addressInfoTag == "c:Country"_L1) {
                                    addressType.setCountry(addressInfo.text());
                                } else if (addressInfoTag == "c:PostalCode"_L1) {
                                    addressType.setPostalCode(addressInfo.text());
                                } else if (addressInfoTag == "c:POBox"_L1) {
                                    addressType.setPostOfficeBox(addressInfo.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " address info tag not supported yet " << addressInfoTag;
                                }
                            }
                            if (!addressType.isEmpty()) {
                                contact.insertAddress(addressType);
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " address tag unknown:" << addressTag;
                        }
                    }
                } else if (tag == "c:PositionCollection"_L1) {
                    for (QDomElement position = e.firstChildElement(); !position.isNull(); position = position.nextSiblingElement()) {
                        const QString positionTag = position.tagName();
                        if (positionTag == "c:Position"_L1) {
                            for (QDomElement positionInfo = position.firstChildElement(); !positionInfo.isNull();
                                 positionInfo = positionInfo.nextSiblingElement()) {
                                const QString positionInfoTag = positionInfo.tagName();
                                if (positionInfoTag == "c:Organization"_L1) {
                                    contact.setOrganization(positionInfo.text());
                                } else if (positionInfoTag == "c:Department"_L1) {
                                    contact.setDepartment(positionInfo.text());
                                } else if (positionInfoTag == "c:Office"_L1) {
                                    contact.setOffice(positionInfo.text());
                                } else if (positionInfoTag == "c:Profession"_L1) {
                                    contact.setProfession(positionInfo.text());
                                } else if (positionInfoTag == "c:Role"_L1) {
                                    contact.setRole(positionInfo.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " position info tag not supported yet " << positionInfoTag;
                                }
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " position tag unknown:" << positionTag;
                        }
                    }
                } else if (tag == "c:Gender"_L1) { // TODO verify it
                    KContacts::Gender gender;
                    const QString genderStr = e.text();
                    if (genderStr == "Male"_L1) {
                        gender.setGender(u"H"_s);
                    } else if (genderStr == "Female"_L1) {
                        gender.setGender(u"F"_s);
                    } else {
                        // Don't provide gender
                        continue;
                    }
                    contact.setGender(gender);
                } else if (tag == "c:Notes"_L1) { // TODO verify it
                    contact.setNote(e.text());
                } else if (tag == "c:UrlCollection"_L1) { // TODO verify it
                    for (QDomElement url = e.firstChildElement(); !url.isNull(); url = url.nextSiblingElement()) {
                        const QString urlTag = url.tagName();
                        if (urlTag == "c:Url"_L1) {
                            for (QDomElement urlInfo = url.firstChildElement(); !urlInfo.isNull(); urlInfo = urlInfo.nextSiblingElement()) {
                                const QString urlInfoTag = urlInfo.tagName();
                                if (urlInfoTag == "c:Value"_L1) {
                                    KContacts::ResourceLocatorUrl resourceLocalUrl;
                                    resourceLocalUrl.setUrl(QUrl::fromUserInput(urlInfo.text()));
                                    contact.insertExtraUrl(resourceLocalUrl);
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " url info tag not supported yet " << urlInfoTag;
                                }
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " url tag unknown:" << urlTag;
                        }
                    }
                } else {
                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "unknown tag " << tag;
                }
            }
            lst << contact;
        }
    }
    return lst;
}

bool ImportWindowContact::loadDomElement(QDomDocument &doc, QFile *file)
{
    const QDomDocument::ParseResult parseResult = doc.setContent(file);
    if (!parseResult) {
        qCDebug(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "Unable to load document.Parse error in line " << parseResult.errorLine << ", col "
                                                      << parseResult.errorColumn << ": " << qPrintable(parseResult.errorMessage);
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
