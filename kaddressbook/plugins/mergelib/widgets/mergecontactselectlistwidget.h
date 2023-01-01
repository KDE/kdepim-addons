/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QIcon>
#include <QWidget>
class QLabel;
class QListWidget;
namespace KContacts
{
class Addressee;
}
namespace KABMergeContacts
{
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectListWidget(QWidget *parent = nullptr);
    ~MergeContactSelectListWidget() override;

    void setContacts(MergeContacts::ConflictInformation conflictType, const KContacts::Addressee::List &lst);
    Q_REQUIRED_RESULT int selectedContact() const;
    MergeContacts::ConflictInformation conflictType() const;
    Q_REQUIRED_RESULT bool verifySelectedInfo() const;

private:
    void fillList(const KContacts::Addressee::List &lst);
    void updateTitle();
    void addItem(const QString &str, const QIcon &icon = QIcon());
    QLabel *mTitle = nullptr;
    QListWidget *const mSelectListWidget;
    MergeContacts::ConflictInformation mConflictType;
};
}
