/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
    ~ResultDuplicateTreeWidgetItem() override;

    Q_REQUIRED_RESULT Akonadi::Item item() const;
    void setItem(const Akonadi::Item &item);

private:
    void setDisplayName();
    Q_REQUIRED_RESULT QString contactName(const KContacts::Addressee &address);
    Akonadi::Item mItem;
};

class KADDRESSBOOKMERGELIB_EXPORT ResultDuplicateTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidget(QWidget *parent = nullptr);
    ~ResultDuplicateTreeWidget();
    void setContacts(const QVector<Akonadi::Item::List> &lstItem);

    Q_REQUIRED_RESULT QVector<Akonadi::Item::List> selectedContactsToMerge() const;

Q_SIGNALS:
    void showContactPreview(const Akonadi::Item &item);
private:
    void slotItemActivated(QTreeWidgetItem *item, int column);
    void slotItemChanged(QTreeWidgetItem *item, int column);
    void changeState(QTreeWidgetItem *item, bool b);
};
}

#endif // RESULTDUPLICATETREEWIDGET_H
