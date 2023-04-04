/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QTreeWidget>
namespace KContacts
{
class Addressee;
}
namespace KABMergeContacts
{
class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit ResultDuplicateTreeWidgetItem(QTreeWidget *parent = nullptr);
    ~ResultDuplicateTreeWidgetItem() override;

    Q_REQUIRED_RESULT Akonadi::Item item() const;
    void setItem(const Akonadi::Item &item);

    Q_REQUIRED_RESULT static QString displayName(const Akonadi::Item &item);

private:
    void setDisplayName();
    Q_REQUIRED_RESULT static QString contactName(const KContacts::Addressee &address);
    Akonadi::Item mItem;
};

class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidget(QWidget *parent = nullptr);
    ~ResultDuplicateTreeWidget() override;
    void setContacts(const QList<Akonadi::Item::List> &lstItem);

    Q_REQUIRED_RESULT QList<Akonadi::Item::List> selectedContactsToMerge() const;

    void checkAllItems();
    void uncheckAllItems();
Q_SIGNALS:
    void showContactPreview(const Akonadi::Item &item);

private:
    void slotItemSelectionChanged();
    void slotItemChanged(QTreeWidgetItem *item, int column);
    void changeState(QTreeWidgetItem *item, bool b);
};
}
