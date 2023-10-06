/*
    SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <KContacts/Addressee>

namespace KABMergeContacts
{
class MergeContacts
{
public:
    explicit MergeContacts(const Akonadi::Item::List &items = Akonadi::Item::List());
    ~MergeContacts();

    enum ConflictInformation {
        None = 0,
        Birthday = 1,
        Geo = 2,
        Photo = 4,
        Logo = 8,
        Anniversary = 16,
        Name = 32,
        NickName = 64,
        Blog = 128,
        HomePage = 256,
        Organization = 512,
        Profession = 1024,
        Title = 2056,
        Departement = 4096,
        Office = 8192,
        ManagerName = 16384,
        Assistant = 32768,
        FreeBusy = 65536,
        FamilyName = 131072,
        PartnerName = 262144,
        Keys = 524288,
    };
    Q_ENUMS(ConflictInformation)
    Q_DECLARE_FLAGS(ConflictInformations, ConflictInformation)

    [[nodiscard]] KContacts::Addressee mergedContact(bool excludeConflictPart = false);

    [[nodiscard]] MergeContacts::ConflictInformations requiresManualSelectionOfInformation();

    void setItems(const Akonadi::Item::List &items);

private:
    void mergeToContact(KContacts::Addressee &newAddress, const KContacts::Addressee &fromContact, bool excludeConflictPart);
    void checkCustomValue(const KContacts::Addressee &address,
                          const QString &variable,
                          KContacts::Addressee &newContact,
                          MergeContacts::ConflictInformations &result,
                          MergeContacts::ConflictInformation conflict);
    void mergeCustomValue(const KContacts::Addressee &fromContact, const QString &variable, KContacts::Addressee &newContact);
    Akonadi::Item::List mListItem;
};
}
