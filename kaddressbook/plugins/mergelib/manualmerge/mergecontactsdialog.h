/*
    Copyright (c) 2013-2017 Montel Laurent <montel@kde.org>

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

#ifndef MERGECONTACTSDIALOG_H
#define MERGECONTACTSDIALOG_H

#include <QDialog>
#include <AkonadiCore/Item>
#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
class QDialogButtonBox;
class QStackedWidget;

namespace KABMergeContacts {
class MergeContactWidget;
class MergeContactErrorLabel;
class MergeContactSelectInformationScrollArea;
class MergeContactInfoWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MergeContactsDialog(QWidget *parent = nullptr);
    ~MergeContactsDialog();

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
