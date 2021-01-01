/*
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSHOWRESULTTABWIDGET_H
#define MERGECONTACTSHOWRESULTTABWIDGET_H

#include <QTabWidget>
#include <AkonadiCore/item.h>

namespace KABMergeContacts {
class MergeContactShowResultTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MergeContactShowResultTabWidget(QWidget *parent = nullptr);
    ~MergeContactShowResultTabWidget() override;

    void updateTabWidget();

    Q_REQUIRED_RESULT bool tabBarVisible() const;

    void showMergedContacts(const Akonadi::Item::List &lstItem);
    void addMergedContact(const Akonadi::Item &item, bool updateTab = false);
};
}
#endif // MERGECONTACTSHOWRESULTTABWIDGET_H
