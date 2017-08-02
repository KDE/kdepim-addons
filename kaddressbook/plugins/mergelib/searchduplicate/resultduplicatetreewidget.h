/*
    Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef RESULTDUPLICATETREEWIDGET_H
#define RESULTDUPLICATETREEWIDGET_H

#include <QTreeWidget>
#include <AkonadiCore/Item>
#include "kaddressbookmergelib_export.h"
namespace KContacts {
class Addressee;
}
namespace KABMergeContacts {
class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit ResultDuplicateTreeWidgetItem(QTreeWidget *parent = nullptr);
    ~ResultDuplicateTreeWidgetItem();

    Akonadi::Item item() const;
    void setItem(const Akonadi::Item &item);

private:
    void setDisplayName();
    QString contactName(const KContacts::Addressee &address);
    Akonadi::Item mItem;
};

class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidget(QWidget *parent = nullptr);
    ~ResultDuplicateTreeWidget();
    void setContacts(const QVector<Akonadi::Item::List> &lstItem);

    QVector<Akonadi::Item::List> selectedContactsToMerge() const;

Q_SIGNALS:
    void showContactPreview(const Akonadi::Item &item);
private:
    void slotItemActivated(QTreeWidgetItem *item, int column);
    void slotItemChanged(QTreeWidgetItem *item, int column);
    void changeState(QTreeWidgetItem *item, bool b);
};
}

#endif // RESULTDUPLICATETREEWIDGET_H
