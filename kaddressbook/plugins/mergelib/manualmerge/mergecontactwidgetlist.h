/*
    SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MERGECONTACTWIDGETLIST_H
#define MERGECONTACTWIDGETLIST_H

#include <QListWidget>
#include <AkonadiCore/Item>
#include <KContacts/Addressee>

namespace KABMergeContacts {
class MergeContactWidgetListItem : public QListWidgetItem
{
public:
    MergeContactWidgetListItem(const Akonadi::Item &item, QListWidget *parent = nullptr);
    Q_REQUIRED_RESULT Akonadi::Item item() const;

private:
    Akonadi::Item mItem;
};

class MergeContactWidgetList : public QListWidget
{
    Q_OBJECT
public:
    explicit MergeContactWidgetList(QWidget *parent = nullptr);
    ~MergeContactWidgetList();

    void fillListContact(const Akonadi::Item::List &items);
    Akonadi::Item::List listSelectedContacts() const;
    Akonadi::Item currentAkonadiItem() const;
private:
    QString itemName(const KContacts::Addressee &address) const;
};
}

#endif // MERGECONTACTWIDGETLIST_H
