/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <QWidget>
class QStackedWidget;
namespace KABMergeContacts
{
class MergeContactSelectInformationWidget;
class MergeContactInfoWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationScrollArea : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationScrollArea(QWidget *parent = nullptr);
    ~MergeContactSelectInformationScrollArea() override;
    void setContacts(MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem, const Akonadi::Collection &col);

private:
    void slotMergeContacts();
    void slotMergeDone(const Akonadi::Item &item);
    void mergeContact(const KContacts::Addressee &addr);
    Akonadi::Collection mCollection;
    Akonadi::Item::List mListItem;
    MergeContactSelectInformationWidget *const mSelectInformationWidget;
    QStackedWidget *const mStackWidget;
    MergeContactInfoWidget *const mMergedContactWidget;
};
}
