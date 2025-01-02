/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QTabWidget>

namespace KABMergeContacts
{
class MergeContactShowResultTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MergeContactShowResultTabWidget(QWidget *parent = nullptr);
    ~MergeContactShowResultTabWidget() override;

    void updateTabWidget();

    [[nodiscard]] bool tabBarVisible() const;

    void showMergedContacts(const Akonadi::Item::List &lstItem);
    void addMergedContact(const Akonadi::Item &item, bool updateTab = false);
};
}
