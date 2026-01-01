/*
    SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <KContacts/Addressee>
#include <QListWidget>

namespace KABMergeContacts
{
class MergeContactWidgetListItem : public QListWidgetItem
{
public:
    explicit MergeContactWidgetListItem(const Akonadi::Item &item, QListWidget *parent = nullptr);
    [[nodiscard]] Akonadi::Item item() const;

private:
    const Akonadi::Item mItem;
};

class MergeContactWidgetList : public QListWidget
{
    Q_OBJECT
public:
    explicit MergeContactWidgetList(QWidget *parent = nullptr);
    ~MergeContactWidgetList() override;

    void fillListContact(const Akonadi::Item::List &items);
    [[nodiscard]] Akonadi::Item::List listSelectedContacts() const;
    [[nodiscard]] Akonadi::Item currentAkonadiItem() const;

private:
    [[nodiscard]] QString itemName(const KContacts::Addressee &address) const;
    void slotCustomContextMenuRequested(const QPoint &);
    void slotSelectAll();
    void slotDeselectAll();
};
}
