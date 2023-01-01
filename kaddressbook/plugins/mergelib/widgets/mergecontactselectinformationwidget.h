/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QWidget>
namespace KABMergeContacts
{
class MergeContactSelectListWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationWidget(QWidget *parent = nullptr);
    ~MergeContactSelectInformationWidget() override;

    void setContacts(KABMergeContacts::MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem);
    void createContact(KContacts::Addressee &addr);

    Q_REQUIRED_RESULT bool verifySelectedInfo() const;

private:
    void addInformationWidget(MergeContacts::ConflictInformation conflictType);
    KContacts::Addressee::List mAddressList;
    QVector<MergeContactSelectListWidget *> mListMergeSelectInformation;
};
}
