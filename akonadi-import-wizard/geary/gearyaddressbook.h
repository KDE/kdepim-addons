/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractAddressBook>

class GearyAddressBook : public LibImportWizard::AbstractAddressBook
{
    Q_OBJECT
public:
    explicit GearyAddressBook(const QString &filename);
    ~GearyAddressBook() override;
    void importAddressBook();
};
