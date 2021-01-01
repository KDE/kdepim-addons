/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef OPERAADDRESSBOOK_H
#define OPERAADDRESSBOOK_H

#include <ImportWizard/AbstractAddressBook>

class OperaAddressBook : public LibImportWizard::AbstractAddressBook
{
public:
    explicit OperaAddressBook(const QString &filename);
    ~OperaAddressBook() override;

    void importAddressBook();
private:
    void appendContact(KContacts::Addressee *contact);
    QString mFileName;
};

#endif // OPERAADDRESSBOOK_H
