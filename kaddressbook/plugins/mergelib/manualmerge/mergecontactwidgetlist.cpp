/*
    SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactwidgetlist.h"

#include <KLocalizedString>
#include <QMenu>

using namespace KABMergeContacts;
MergeContactWidgetList::MergeContactWidgetList(QWidget *parent)
    : QListWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MergeContactWidgetList::customContextMenuRequested, this, &MergeContactWidgetList::slotCustomContextMenuRequested);
}

MergeContactWidgetList::~MergeContactWidgetList() = default;

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

void MergeContactWidgetList::slotCustomContextMenuRequested(const QPoint &)
{
    QMenu menu(this);
    menu.addAction(i18n("Select All"), this, &MergeContactWidgetList::slotSelectAll);
    menu.addAction(i18n("Deselect All"), this, &MergeContactWidgetList::slotDeselectAll);
    menu.exec(QCursor::pos());
}

void MergeContactWidgetList::slotSelectAll()
{
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        itemWidget->setCheckState(Qt::Checked);
    }
}

void MergeContactWidgetList::slotDeselectAll()
{
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *itemWidget = item(i);
        itemWidget->setCheckState(Qt::Unchecked);
    }
}

void MergeContactWidgetList::fillListContact(const Akonadi::Item::List &items)
{
    clear();
    for (const Akonadi::Item &item : items) {
        if (item.hasPayload<KContacts::Addressee>()) {
            auto widgetItem = new MergeContactWidgetListItem(item, this);
            auto address = item.payload<KContacts::Addressee>();

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
    return {};
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

#include "moc_mergecontactwidgetlist.cpp"
