/*
    SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QDialog>
class QDialogButtonBox;
class QStackedWidget;

namespace KABMergeContacts
{
class MergeContactWidget;
class MergeContactErrorLabel;
class MergeContactSelectInformationScrollArea;
class MergeContactInfoWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MergeContactsDialog(QWidget *parent = nullptr);
    ~MergeContactsDialog() override;

    void setContacts(const Akonadi::Item::List &list);

private:
    void slotCustomizeMergeContact(const Akonadi::Item::List &lst, MergeContacts::ConflictInformations conflictType, const Akonadi::Collection &col);
    void slotContactMerged(const Akonadi::Item &item);
    void readConfig();
    void writeConfig();
    QDialogButtonBox *const mButtonBox;
    QStackedWidget *const mStackedWidget;
    KABMergeContacts::MergeContactErrorLabel *const mNoEnoughContactSelected;
    KABMergeContacts::MergeContactErrorLabel *const mNoContactSelected;
    KABMergeContacts::MergeContactWidget *const mManualMergeResultWidget;
    KABMergeContacts::MergeContactSelectInformationScrollArea *const mSelectInformation;
    KABMergeContacts::MergeContactInfoWidget *const mMergeContactInfo;
};
}
