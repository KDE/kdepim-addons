/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractAddressBook>

class OperaAddressBook : public LibImportWizard::AbstractAddressBook
{
public:
    explicit OperaAddressBook(const QString &filename);
    ~OperaAddressBook() override;

    void importAddressBook();

private:
    void appendContact(KContacts::Addressee *contact);
    const QString mFileName;
};
