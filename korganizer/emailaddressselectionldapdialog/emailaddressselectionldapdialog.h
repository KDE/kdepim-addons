/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <Akonadi/Contact/AbstractEmailAddressSelectionDialog>
namespace Akonadi
{
class RecipientsPickerWidget;
}

namespace PimCommon
{
class LdapSearchDialog;
}

class EmailAddressSelectionLdapDialog : public Akonadi::AbstractEmailAddressSelectionDialog
{
    Q_OBJECT
public:
    explicit EmailAddressSelectionLdapDialog(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~EmailAddressSelectionLdapDialog() override;

    Q_REQUIRED_RESULT Akonadi::EmailAddressSelection::List selectedAddresses() const override;
    Akonadi::EmailAddressSelectionWidget *view() const override;

private:
    void writeConfig();
    void readConfig();
    void slotSearchLDAP();
    void ldapSearchResult();
    Akonadi::RecipientsPickerWidget *const mView;
    PimCommon::LdapSearchDialog *mLdapSearchDialog = nullptr;
};

