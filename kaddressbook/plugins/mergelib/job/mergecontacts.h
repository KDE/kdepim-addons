/*
    Copyright (c) 2014-2020 Laurent Montel <montel@kde.org>

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

#ifndef MERGECONTACTS_H
#define MERGECONTACTS_H

#include <AkonadiCore/Item>
#include <KContacts/Addressee>

namespace KABMergeContacts {
class MergeContacts
{
public:
    MergeContacts(const Akonadi::Item::List &items = Akonadi::Item::List());
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
        Keys = 524288
    };
    Q_ENUMS(ConflictInformation)
    Q_DECLARE_FLAGS(ConflictInformations, ConflictInformation)

    Q_REQUIRED_RESULT KContacts::Addressee mergedContact(bool excludeConflictPart = false);

    Q_REQUIRED_RESULT MergeContacts::ConflictInformations requiresManualSelectionOfInformation();

    void setItems(const Akonadi::Item::List &items);
private:
    void mergeToContact(KContacts::Addressee &newAddress, const KContacts::Addressee &fromContact, bool excludeConflictPart);
    void checkCustomValue(const KContacts::Addressee &address, const QString &variable, KContacts::Addressee &newContact, MergeContacts::ConflictInformations &result, MergeContacts::ConflictInformation conflict);
    void mergeCustomValue(const KContacts::Addressee &fromContact, const QString &variable, KContacts::Addressee &newContact);
    Akonadi::Item::List mListItem;
};
}

#endif // MERGECONTACTS_H
