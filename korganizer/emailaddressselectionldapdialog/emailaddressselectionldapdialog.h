/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
#ifndef EMAILADDRESSSELECTIONLDAPDIALOG_H
#define EMAILADDRESSSELECTIONLDAPDIALOG_H

#include <Akonadi/Contact/AbstractEmailAddressSelectionDialog>
namespace Akonadi {
class RecipientsPickerWidget;
}

namespace PimCommon {
class LdapSearchDialog;
}

class EmailAddressSelectionLdapDialog : public Akonadi::AbstractEmailAddressSelectionDialog
{
    Q_OBJECT
public:
    explicit EmailAddressSelectionLdapDialog(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~EmailAddressSelectionLdapDialog() override;

    Akonadi::EmailAddressSelection::List selectedAddresses() const override;
    Akonadi::EmailAddressSelectionWidget *view() const override;
private:
    void writeConfig();
    void readConfig();
    void slotSearchLDAP();
    void ldapSearchResult();
    Akonadi::RecipientsPickerWidget *mView = nullptr;
    PimCommon::LdapSearchDialog *mLdapSearchDialog = nullptr;
};

#endif // EMAILADDRESSSELECTIONLDAPDIALOG_H
