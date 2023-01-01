/*
    SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "resultduplicatetreewidget.h"
#include <KLocalizedString>

#include <KContacts/Addressee>

using namespace KABMergeContacts;

ResultDuplicateTreeWidget::ResultDuplicateTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    setHeaderLabel(i18n("Contacts"));
    connect(this, &QTreeWidget::itemSelectionChanged, this, &ResultDuplicateTreeWidget::slotItemSelectionChanged);
    connect(this, &ResultDuplicateTreeWidget::itemChanged, this, &ResultDuplicateTreeWidget::slotItemChanged);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

ResultDuplicateTreeWidget::~ResultDuplicateTreeWidget() = default;

void ResultDuplicateTreeWidget::slotItemChanged(QTreeWidgetItem *item, int column)
{
    if (column != 0) {
        return;
    }
    // Parent
    if (item->childCount() != 0) {
        changeState(item, item->checkState(0) == Qt::Checked);
    } else { // child
        QTreeWidgetItem *parent = item->parent();
        if (parent) {
            blockSignals(true);
            Qt::CheckState state = Qt::PartiallyChecked;
            for (int i = 0; i < parent->childCount(); ++i) {
                if (i == 0) {
                    state = parent->child(i)->checkState(0);
                } else {
                    if (state != parent->child(i)->checkState(0)) {
                        state = Qt::PartiallyChecked;
                        break;
                    }
                }
            }
            parent->setCheckState(0, state);
            blockSignals(false);
        }
    }
}

void ResultDuplicateTreeWidget::changeState(QTreeWidgetItem *item, bool b)
{
    blockSignals(true);
    item->setCheckState(0, b ? Qt::Checked : Qt::Unchecked);
    for (int i = 0; i < item->childCount(); ++i) {
        item->child(i)->setCheckState(0, b ? Qt::Checked : Qt::Unchecked);
    }
    blockSignals(false);
}

void ResultDuplicateTreeWidget::slotItemSelectionChanged()
{
    auto resultItem = dynamic_cast<ResultDuplicateTreeWidgetItem *>(currentItem());
    if (resultItem) {
        Q_EMIT showContactPreview(resultItem->item());
    }
}

void ResultDuplicateTreeWidget::setContacts(const QVector<Akonadi::Item::List> &lstItem)
{
    clear();
    int i = 1;
    for (const Akonadi::Item::List &lst : lstItem) {
        auto topLevelItem = new ResultDuplicateTreeWidgetItem(this);
        topLevelItem->setText(
            0,
            i18n("Duplicate contact \"%1\" (%2 times)", ResultDuplicateTreeWidgetItem::displayName(lst.first()), QString::number(lst.count())));
        for (const Akonadi::Item &item : lst) {
            auto childItem = new ResultDuplicateTreeWidgetItem;
            topLevelItem->addChild(childItem);
            childItem->setItem(item);
        }
        ++i;
    }
    expandAll();
}

QVector<Akonadi::Item::List> ResultDuplicateTreeWidget::selectedContactsToMerge() const
{
    QVector<Akonadi::Item::List> listItems;
    for (int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);
        const int childCount = item->childCount();
        if (childCount > 0) {
            Akonadi::Item::List items;
            for (int child = 0; child < childCount; ++child) {
                auto childItem = static_cast<ResultDuplicateTreeWidgetItem *>(item->child(child));
                if (childItem->checkState(0) == Qt::Checked) {
                    items << childItem->item();
                }
            }
            if (items.count() > 1) {
                listItems << items;
            }
        }
    }
    return listItems;
}

void ResultDuplicateTreeWidget::checkAllItems()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);
        item->setCheckState(0, Qt::Checked);
    }
}

void ResultDuplicateTreeWidget::uncheckAllItems()
{
    for (int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);
        item->setCheckState(0, Qt::Unchecked);
    }
}

ResultDuplicateTreeWidgetItem::ResultDuplicateTreeWidgetItem(QTreeWidget *parent)
    : QTreeWidgetItem(parent)
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    setCheckState(0, Qt::Unchecked);
}

ResultDuplicateTreeWidgetItem::~ResultDuplicateTreeWidgetItem() = default;

Akonadi::Item ResultDuplicateTreeWidgetItem::item() const
{
    return mItem;
}

void ResultDuplicateTreeWidgetItem::setItem(const Akonadi::Item &item)
{
    mItem = item;
    setDisplayName();
}

QString ResultDuplicateTreeWidgetItem::contactName(const KContacts::Addressee &address)
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

void ResultDuplicateTreeWidgetItem::setDisplayName()
{
    if (mItem.isValid()) {
        setText(0, displayName(mItem));
    }
}

QString ResultDuplicateTreeWidgetItem::displayName(const Akonadi::Item &item)
{
    if (item.isValid()) {
        const auto address = item.payload<KContacts::Addressee>();
        return contactName(address);
    }
    return {};
}
