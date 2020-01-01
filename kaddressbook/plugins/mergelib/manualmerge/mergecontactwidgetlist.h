/*
    Copyright (c) 2014-2020 Laurent Montel <montel@kde.org>

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
