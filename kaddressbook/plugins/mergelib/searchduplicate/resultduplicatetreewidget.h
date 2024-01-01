/*
    SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] Akonadi::Item item() const;
    void setItem(const Akonadi::Item &item);

    [[nodiscard]] static QString displayName(const Akonadi::Item &item);

private:
    void setDisplayName();
    [[nodiscard]] static QString contactName(const KContacts::Addressee &address);
    Akonadi::Item mItem;
};

class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidget(QWidget *parent = nullptr);
    ~ResultDuplicateTreeWidget() override;
    void setContacts(const QList<Akonadi::Item::List> &lstItem);

    [[nodiscard]] QList<Akonadi::Item::List> selectedContactsToMerge() const;

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
