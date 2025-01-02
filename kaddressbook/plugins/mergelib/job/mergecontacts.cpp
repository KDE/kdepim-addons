/*
    SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontacts.h"
#include "kaddressbookmergelibprivate_debug.h"

using namespace KABMergeContacts;
using namespace KContacts;
MergeContacts::MergeContacts(const Akonadi::Item::List &items)
    : mListItem(items)
{
}

MergeContacts::~MergeContacts() = default;

void MergeContacts::setItems(const Akonadi::Item::List &items)
{
    mListItem = items;
}

KContacts::Addressee MergeContacts::mergedContact(bool excludeConflictPart)
{
    KContacts::Addressee newContact;
    if (mListItem.count() <= 1) {
        return newContact;
    }
    bool firstAddress = true;
    for (const Akonadi::Item &item : std::as_const(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            auto address = item.payload<KContacts::Addressee>();
            if (firstAddress) {
                firstAddress = false;
                newContact = address;
            } else {
                mergeToContact(newContact, address, excludeConflictPart);
            }
        }
    }
    return newContact;
}

void MergeContacts::mergeToContact(KContacts::Addressee &newContact, const KContacts::Addressee &fromContact, bool excludeConflictPart)
{
    // Duplicate notes.
    const QString fromContactNote = fromContact.note();
    if (!fromContactNote.isEmpty()) {
        QString newContactNote = newContact.note();
        if (!newContactNote.isEmpty()) {
            newContactNote += QLatin1Char('\n');
        }
        newContactNote += fromContactNote;
        newContact.setNote(newContactNote);
    }
    // Duplicate emails
    const QStringList emails = fromContact.emails();
    if (!emails.isEmpty()) {
        QStringList newContactsEmail = newContact.emails();
        for (const QString &email : emails) {
            if (!newContactsEmail.contains(email)) {
                newContactsEmail.append(email);
            }
        }
        newContact.setEmails(newContactsEmail);
    }
    // Merge Categories
    const QStringList categories = fromContact.categories();
    if (!categories.isEmpty()) {
        QStringList newContactsCategories = newContact.categories();
        for (const QString &category : categories) {
            if (!newContactsCategories.contains(category)) {
                newContactsCategories.append(category);
            }
        }
        newContact.setCategories(newContactsCategories);
    }

    // Merge Phone
    const PhoneNumber::List listPhone = fromContact.phoneNumbers();
    if (!listPhone.isEmpty()) {
        const PhoneNumber::List newContactsPhone = newContact.phoneNumbers();
        for (const PhoneNumber &phone : listPhone) {
            if (!newContactsPhone.contains(phone)) {
                newContact.insertPhoneNumber(phone);
            }
        }
    }

    // Merge Address
    const Address::List listAddress = fromContact.addresses();
    if (!listAddress.isEmpty()) {
        const Address::List newContactsAddress = newContact.addresses();
        for (const Address &addr : listAddress) {
            if (!newContactsAddress.contains(addr)) {
                newContact.insertAddress(addr);
            }
        }
    }

    // Merge Impp
    const Impp::List listImpp = fromContact.imppList();
    if (!listImpp.isEmpty()) {
        const Impp::List newContactsImpp = newContact.imppList();
        for (const Impp &impp : listImpp) {
            if (!newContactsImpp.contains(impp)) {
                newContact.insertImpp(impp);
            }
        }
    }

    if (!excludeConflictPart) {
        // Merge Name
        if (newContact.name().isEmpty() && !fromContact.name().isEmpty()) {
            newContact.setName(fromContact.name());
        }
        // Merge organization
        if (newContact.organization().isEmpty() && !fromContact.organization().isEmpty()) {
            newContact.setOrganization(fromContact.organization());
        }
        // Merge NickName
        if (newContact.nickName().isEmpty() && !fromContact.nickName().isEmpty()) {
            newContact.setNickName(fromContact.nickName());
        }
        // Merge Title
        if (newContact.title().isEmpty() && !fromContact.title().isEmpty()) {
            newContact.setTitle(fromContact.title());
        }
        // Merge Departement
        if (newContact.department().isEmpty() && !fromContact.department().isEmpty()) {
            newContact.setDepartment(fromContact.department());
        }
        // Merge FamilyName
        if (newContact.familyName().isEmpty() && !fromContact.familyName().isEmpty()) {
            newContact.setFamilyName(fromContact.familyName());
        }
        // Merge HomePage
        if (newContact.url().url().isEmpty() && !fromContact.url().url().isEmpty()) {
            newContact.setUrl(fromContact.url());
        }
        // Merge geo
        if (newContact.geo().isValid() && !fromContact.geo().isValid()) {
            newContact.setGeo(fromContact.geo());
        }
        // Merge Photo
        if (newContact.photo().isEmpty() && !fromContact.photo().isEmpty()) {
            newContact.setPhoto(fromContact.photo());
        }

        // Merge Birthday
        if (!newContact.birthday().isValid() && !fromContact.birthday().isValid()) {
            newContact.setBirthday(fromContact.birthday());
        }

        // Merge Logo
        if (newContact.logo().isEmpty() && !fromContact.logo().isEmpty()) {
            newContact.setLogo(fromContact.logo());
        }

        // Merge Blog
        mergeCustomValue(fromContact, QStringLiteral("BlogFeed"), newContact);
        // Merge profession
        mergeCustomValue(fromContact, QStringLiteral("X-Profession"), newContact);
        // Merge Office
        mergeCustomValue(fromContact, QStringLiteral("X-Office"), newContact);
        // Merge ManagersName
        mergeCustomValue(fromContact, QStringLiteral("X-ManagersName"), newContact);
        // Merge AssistantsName
        mergeCustomValue(fromContact, QStringLiteral("X-AssistantsName"), newContact);
        // Merge SpousesName
        mergeCustomValue(fromContact, QStringLiteral("X-SpousesName"), newContact);
        // Merge Anniversary
        mergeCustomValue(fromContact, QStringLiteral("X-Anniversary"), newContact);
        // Merge Key
    }
}

void MergeContacts::mergeCustomValue(const KContacts::Addressee &fromContact, const QString &variable, KContacts::Addressee &newContact)
{
    const QString newValue = newContact.custom(QStringLiteral("KADDRESSBOOK"), variable);
    const QString value = fromContact.custom(QStringLiteral("KADDRESSBOOK"), variable);
    if (newValue.isEmpty() && !value.isEmpty()) {
        newContact.insertCustom(QStringLiteral("KADDRESSBOOK"), variable, value);
    }
}

MergeContacts::ConflictInformations MergeContacts::requiresManualSelectionOfInformation()
{
    MergeContacts::ConflictInformations result = None;
    if (mListItem.count() < 2) {
        return result;
    }
    KContacts::Addressee newContact;
    for (const Akonadi::Item &item : std::as_const(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const auto address = item.payload<KContacts::Addressee>();
            // Test Birthday
            if (address.birthday().date().isValid()) {
                if (newContact.birthday().date().isValid()) {
                    if (newContact.birthday().date() != address.birthday().date()) {
                        result |= Birthday;
                    }
                } else {
                    newContact.setBirthday(address.birthday());
                }
            }

            // Test Geo
            const KContacts::Geo geo = address.geo();
            if (geo.isValid()) {
                if (newContact.geo().isValid()) {
                    if (newContact.geo() != geo) {
                        result |= Geo;
                    }
                } else {
                    newContact.setGeo(address.geo());
                }
            }
            // Test Photo
            const KContacts::Picture photo = address.photo();
            if (!photo.isEmpty()) {
                if (!newContact.photo().isEmpty()) {
                    if (newContact.photo() != photo) {
                        result |= Photo;
                    }
                } else {
                    newContact.setPhoto(address.photo());
                }
            }
            // Test Logo
            const KContacts::Picture logo = address.logo();
            if (!logo.isEmpty()) {
                if (!newContact.logo().isEmpty()) {
                    if (newContact.logo() != logo) {
                        result |= Logo;
                    }
                } else {
                    newContact.setLogo(address.logo());
                }
            }
            // Test Name
            const QString name = address.name();
            if (!name.isEmpty()) {
                if (!newContact.name().isEmpty()) {
                    if (newContact.name() != name) {
                        result |= Name;
                    }
                } else {
                    newContact.setName(address.name());
                }
            }
            // Test NickName
            const QString nickName = address.nickName();
            if (!nickName.isEmpty()) {
                if (!newContact.nickName().isEmpty()) {
                    if (newContact.nickName() != nickName) {
                        result |= NickName;
                    }
                } else {
                    newContact.setNickName(address.nickName());
                }
            }
            // Test Organization
            const QString organization = address.organization();
            if (!organization.isEmpty()) {
                if (!newContact.organization().isEmpty()) {
                    if (newContact.organization() != organization) {
                        result |= Organization;
                    }
                } else {
                    newContact.setOrganization(address.organization());
                }
            }
            // Test Title
            const QString title = address.title();
            if (!title.isEmpty()) {
                if (!newContact.title().isEmpty()) {
                    if (newContact.title() != title) {
                        result |= Title;
                    }
                } else {
                    newContact.setTitle(address.title());
                }
            }
            // Test Departement
            const QString departement = address.department();
            if (!departement.isEmpty()) {
                if (!newContact.department().isEmpty()) {
                    if (newContact.department() != departement) {
                        result |= Departement;
                    }
                } else {
                    newContact.setDepartment(address.department());
                }
            }
            // Test HomePage
            const QUrl url = address.url().url();
            if (url.isValid() && !url.isEmpty()) {
                if (newContact.url().url().isValid() && !newContact.url().url().isEmpty()) {
                    if (newContact.url().url() != url) {
                        result |= HomePage;
                    }
                } else {
                    newContact.setUrl(address.url());
                }
            }
            // Test FamilyName
            const QString familyName = address.familyName();
            if (!familyName.isEmpty()) {
                if (!newContact.familyName().isEmpty()) {
                    if (newContact.familyName() != familyName) {
                        result |= FamilyName;
                    }
                } else {
                    newContact.setFamilyName(address.familyName());
                }
            }
            // Test Blog
            checkCustomValue(address, QStringLiteral("BlogFeed"), newContact, result, Blog);
            // Test profession
            checkCustomValue(address, QStringLiteral("X-Profession"), newContact, result, Profession);
            // Test profession
            checkCustomValue(address, QStringLiteral("X-Office"), newContact, result, Office);
            // Test ManagersName
            checkCustomValue(address, QStringLiteral("X-ManagersName"), newContact, result, ManagerName);
            // Test AssistantsName
            checkCustomValue(address, QStringLiteral("X-AssistantsName"), newContact, result, Assistant);
            // Test SpousesName
            checkCustomValue(address, QStringLiteral("X-SpousesName"), newContact, result, PartnerName);
            // Test Anniversary
            checkCustomValue(address, QStringLiteral("X-Anniversary"), newContact, result, Anniversary);
        }
    }
    qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " result " << result;
    return result;
}

void MergeContacts::checkCustomValue(const KContacts::Addressee &address,
                                     const QString &variable,
                                     KContacts::Addressee &newContact,
                                     MergeContacts::ConflictInformations &result,
                                     MergeContacts::ConflictInformation conflict)
{
    const QString value = address.custom(QStringLiteral("KADDRESSBOOK"), variable);
    if (!value.isEmpty()) {
        const QString newValue = newContact.custom(QStringLiteral("KADDRESSBOOK"), variable);
        if (!newValue.isEmpty()) {
            if (newValue != value) {
                result |= conflict;
            }
        } else {
            newContact.insertCustom(QStringLiteral("KADDRESSBOOK"), variable, value);
        }
    }
}
