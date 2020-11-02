/*
    SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactwidgetlist.h"

using namespace KABMergeContacts;
MergeContactWidgetList::MergeContactWidgetList(QWidget *parent)
    : QListWidget(parent)
{
}

MergeContactWidgetList::~MergeContactWidgetList()
{
}

QString MergeContactWidgetList::itemName(const KContacts::Addressee &address) const
{
    const QString realName = address.realName();
    if (!realName.isEmpty()) {
        return realName;
    }
    const QString name = address.name();
    if (!name.isEmpty()) {
        return name;
    }
    return address.fullEmail();
}

void MergeContactWidgetList::fillListContact(const Akonadi::Item::List &items)
{
    clear();
    for (const Akonadi::Item &item : items) {
        if (item.hasPayload<KContacts::Addressee>()) {
            auto *widgetItem = new MergeContactWidgetListItem(item, this);
            KContacts::Addressee address = item.payload<KContacts::Addressee>();

            widgetItem->setText(itemName(address));
        }
    }
}

Akonadi::Item::List MergeContactWidgetList::listSelectedContacts() const
{
    Akonadi::Item::List lstItems;
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        if (itemWidget->checkState() == Qt::Checked) {
            lstItems.append((static_cast<MergeContactWidgetListItem *>(itemWidget))->item());
        }
    }
    return lstItems;
}

Akonadi::Item MergeContactWidgetList::currentAkonadiItem() const
{
    QListWidgetItem *curr = currentItem();
    if (curr) {
        return (static_cast<MergeContactWidgetListItem *>(curr))->item();
    }
    return Akonadi::Item();
}

MergeContactWidgetListItem::MergeContactWidgetListItem(const Akonadi::Item &item, QListWidget *parent)
    : QListWidgetItem(parent)
    , mItem(item)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}

Akonadi::Item MergeContactWidgetListItem::item() const
{
    return mItem;
}
