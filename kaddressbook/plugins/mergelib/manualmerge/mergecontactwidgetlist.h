/*
    SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

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
    ~MergeContactWidgetList() override;

    void fillListContact(const Akonadi::Item::List &items);
    Akonadi::Item::List listSelectedContacts() const;
    Akonadi::Item currentAkonadiItem() const;

private:
    QString itemName(const KContacts::Addressee &address) const;
};
}

