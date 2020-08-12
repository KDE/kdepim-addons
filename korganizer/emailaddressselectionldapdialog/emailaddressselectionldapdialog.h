/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
