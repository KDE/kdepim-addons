/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GearyAddressBook_H
#define GearyAddressBook_H

#include <ImportWizard/AbstractAddressBook>
#include <QHash>

class GearyAddressBook : public LibImportWizard::AbstractAddressBook
{
    Q_OBJECT
public:
    explicit GearyAddressBook(const QString &filename);
    ~GearyAddressBook() override;
    void importAddressBook();
};

#endif /* GearyAddressBook_H */
