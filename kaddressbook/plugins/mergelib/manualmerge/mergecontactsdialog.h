/*
    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MERGECONTACTSDIALOG_H
#define MERGECONTACTSDIALOG_H

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <AkonadiCore/Item>
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
    QDialogButtonBox *mButtonBox = nullptr;
    QStackedWidget *mStackedWidget = nullptr;
    KABMergeContacts::MergeContactErrorLabel *mNoEnoughContactSelected = nullptr;
    KABMergeContacts::MergeContactErrorLabel *mNoContactSelected = nullptr;
    KABMergeContacts::MergeContactWidget *mManualMergeResultWidget = nullptr;
    KABMergeContacts::MergeContactSelectInformationScrollArea *mSelectInformation = nullptr;
    KABMergeContacts::MergeContactInfoWidget *mMergeContactInfo = nullptr;
};
}
#endif // MERGECONTACTSDIALOG_H
