/*
    SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QWidget>

class QPushButton;
namespace Akonadi
{
class CollectionComboBox;
}
namespace KABMergeContacts
{
class MergeContactWidgetList;
class MergeContactLoseInformationWarning;
class MergeContactInfoWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactWidget(QWidget *parent = nullptr);
    ~MergeContactWidget() override;

    void setContacts(const Akonadi::Item::List &items);

Q_SIGNALS:
    void
    customizeMergeContact(const Akonadi::Item::List &lst, KABMergeContacts::MergeContacts::ConflictInformations conflictType, const Akonadi::Collection &col);
    void contactMerged(const Akonadi::Item &item);

private:
    void slotUpdateMergeButton();
    void slotMergeContacts();
    void slotAutomaticMerging();
    void slotCustomizeMergingContacts();
    void slotMergeDone(const Akonadi::Item &item);
    Akonadi::Item::List listSelectedContacts() const;
    Akonadi::Item currentItem() const;
    MergeContacts::ConflictInformations mConflictTypes;
    Akonadi::Item::List mSelectedItems;
    Akonadi::Item::List mItems;
    MergeContactWidgetList *const mListWidget;
    QPushButton *const mMergeButton;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    MergeContactLoseInformationWarning *const mMergeContactWarning;
    MergeContactInfoWidget *const mMergeContactInfoWidget;
};
}
