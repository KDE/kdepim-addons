/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importwindowcontact.h"
#include "importexportwindowscontactplugin_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QDomDocument>
#include <QFile>

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
                contact.setUid(QStringLiteral("foo"));
            }
            for (QDomElement e = list.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
                const QString tag = e.tagName();
                if (tag == QLatin1StringView("c:EmailAddressCollection")) {
                    KContacts::Email::List lstEmails;
                    for (QDomElement emails = e.firstChildElement(); !emails.isNull(); emails = emails.nextSiblingElement()) {
                        const QString emailsTag = emails.tagName();
                        if (emailsTag == QLatin1StringView("c:EmailAddress")) {
                            KContacts::Email email;
                            for (QDomElement addresses = emails.firstChildElement(); !addresses.isNull(); addresses = addresses.nextSiblingElement()) {
                                const QString addressesTag = addresses.tagName();
                                if (addressesTag == QLatin1StringView("c:Type")) {
                                } else if (addressesTag == QLatin1StringView("c:Address")) {
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
                } else if (tag == QLatin1StringView("c:NameCollection")) {
                    for (QDomElement name = e.firstChildElement(); !name.isNull(); name = name.nextSiblingElement()) {
                        const QString nameTag = name.tagName();
                        if (nameTag == QLatin1StringView("c:Name")) {
                            for (QDomElement nameInfo = name.firstChildElement(); !nameInfo.isNull(); nameInfo = nameInfo.nextSiblingElement()) {
                                const QString nameInfoTag = nameInfo.tagName();
                                if (nameInfoTag == QLatin1StringView("c:FormattedName")) {
                                    contact.setName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:GivenName")) {
                                    contact.setGivenName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:FamilyName")) {
                                    contact.setFamilyName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:FormattedName")) {
                                    contact.setFormattedName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:Title")) {
                                    contact.setTitle(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:NickName")) {
                                    contact.setNickName(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:Prefix")) {
                                    contact.setPrefix(nameInfo.text());
                                } else if (nameInfoTag == QLatin1StringView("c:Suffix")) {
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
                } else if (tag == QLatin1StringView("c:PhoneNumberCollection")) {
                    for (QDomElement number = e.firstChildElement(); !number.isNull(); number = number.nextSiblingElement()) {
                        const QString numberTag = number.tagName();
                        if (numberTag == QLatin1StringView("c:PhoneNumber")) {
                            KContacts::PhoneNumber phoneNumber;
                            for (QDomElement numberInfo = number.firstChildElement(); !numberInfo.isNull(); numberInfo = numberInfo.nextSiblingElement()) {
                                const QString numberInfoTag = numberInfo.tagName();
                                if (numberInfoTag == QLatin1StringView("c:Number")) {
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
                } else if (tag == QLatin1StringView("c:IMAddressCollection")) {
                    for (QDomElement im = e.firstChildElement(); !im.isNull(); im = im.nextSiblingElement()) {
                        const QString imTag = im.tagName();
                        if (imTag == QLatin1StringView("c:IMAddress")) {
                            KContacts::Impp impp;
                            for (QDomElement imInfo = im.firstChildElement(); !imInfo.isNull(); imInfo = imInfo.nextSiblingElement()) {
                                const QString imInfoTag = imInfo.tagName();
                                if (imInfoTag == QLatin1StringView("c:Value")) {
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
                } else if (tag == QLatin1StringView("c:PhotoCollection")) {
                    for (QDomElement photo = e.firstChildElement(); !photo.isNull(); photo = photo.nextSiblingElement()) {
                        const QString photoTag = photo.tagName();
                        if (photoTag == QLatin1StringView("c:Photo")) {
                            KContacts::Picture picture;
                            for (QDomElement photoInfo = photo.firstChildElement(); !photoInfo.isNull(); photoInfo = photoInfo.nextSiblingElement()) {
                                const QString photoInfoTag = photoInfo.tagName();
                                if (photoInfoTag == QLatin1StringView("c:Value")) {
                                    const QString contentType = photoInfo.attribute(QStringLiteral("c:ContentType"));
                                    picture.setRawData(photoInfo.text().toUtf8(), contentType);
                                } else if (photoInfoTag == QLatin1StringView("c:Url")) {
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
                } else if (tag == QLatin1StringView("c:PhysicalAddressCollection")) {
                    for (QDomElement address = e.firstChildElement(); !address.isNull(); address = address.nextSiblingElement()) {
                        const QString addressTag = address.tagName();
                        if (addressTag == QLatin1StringView("c:PhysicalAddress")) {
                            KContacts::Address addressType;
                            for (QDomElement addressInfo = address.firstChildElement(); !addressInfo.isNull(); addressInfo = addressInfo.nextSiblingElement()) {
                                const QString addressInfoTag = addressInfo.tagName();
                                if (addressInfoTag == QLatin1StringView("c:AddressLabel")) {
                                    addressType.setLabel(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:Street")) {
                                    addressType.setStreet(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:Locality")) {
                                    addressType.setLocality(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:Region")) {
                                    addressType.setRegion(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:Country")) {
                                    addressType.setCountry(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:PostalCode")) {
                                    addressType.setPostalCode(addressInfo.text());
                                } else if (addressInfoTag == QLatin1StringView("c:POBox")) {
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
                } else if (tag == QLatin1StringView("c:PositionCollection")) {
                    for (QDomElement position = e.firstChildElement(); !position.isNull(); position = position.nextSiblingElement()) {
                        const QString positionTag = position.tagName();
                        if (positionTag == QLatin1StringView("c:Position")) {
                            for (QDomElement positionInfo = position.firstChildElement(); !positionInfo.isNull();
                                 positionInfo = positionInfo.nextSiblingElement()) {
                                const QString positionInfoTag = positionInfo.tagName();
                                if (positionInfoTag == QLatin1StringView("c:Organization")) {
                                    contact.setOrganization(positionInfo.text());
                                } else if (positionInfoTag == QLatin1StringView("c:Department")) {
                                    contact.setDepartment(positionInfo.text());
                                } else if (positionInfoTag == QLatin1StringView("c:Office")) {
                                    contact.setOffice(positionInfo.text());
                                } else if (positionInfoTag == QLatin1StringView("c:Profession")) {
                                    contact.setProfession(positionInfo.text());
                                } else if (positionInfoTag == QLatin1StringView("c:Role")) {
                                    contact.setRole(positionInfo.text());
                                } else {
                                    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " position info tag not supported yet " << positionInfoTag;
                                }
                            }
                        } else {
                            qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << " position tag unknown:" << positionTag;
                        }
                    }
                } else if (tag == QLatin1StringView("c:Gender")) { // TODO verify it
                    KContacts::Gender gender;
                    const QString genderStr = e.text();
                    if (genderStr == QLatin1StringView("Male")) {
                        gender.setGender(QStringLiteral("H"));
                    } else if (genderStr == QLatin1StringView("Female")) {
                        gender.setGender(QStringLiteral("F"));
                    } else {
                        // Don't provide gender
                        continue;
                    }
                    contact.setGender(gender);
                } else if (tag == QLatin1StringView("c:Notes")) { // TODO verify it
                    contact.setNote(e.text());
                } else if (tag == QLatin1StringView("c:UrlCollection")) { // TODO verify it
                    for (QDomElement url = e.firstChildElement(); !url.isNull(); url = url.nextSiblingElement()) {
                        const QString urlTag = url.tagName();
                        if (urlTag == QLatin1StringView("c:Url")) {
                            for (QDomElement urlInfo = url.firstChildElement(); !urlInfo.isNull(); urlInfo = urlInfo.nextSiblingElement()) {
                                const QString urlInfoTag = urlInfo.tagName();
                                if (urlInfoTag == QLatin1StringView("c:Value")) {
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
