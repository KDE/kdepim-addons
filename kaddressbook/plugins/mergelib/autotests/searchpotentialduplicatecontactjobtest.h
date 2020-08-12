/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SEARCHPOTENTIALDUPLICATECONTACTJOBTEST_H
#define SEARCHPOTENTIALDUPLICATECONTACTJOBTEST_H

#include <QObject>

class SearchPotentialDuplicateContactJobTest : public QObject
{
    Q_OBJECT
public:
    SearchPotentialDuplicateContactJobTest();
private Q_SLOTS:
    void shouldReturnEmptyListWhenNoItem();
    void shouldReturnEmptyListWhenOneItem();
    void shouldReturnListWhenTwoItemsAreDuplicated();
    void shouldReturnListWhenThreeItemsAreDuplicated();
    void shouldReturnTwoList();
    void shouldReturnList_data();
    void shouldReturnList();
};

#endif // SEARCHPOTENTIALDUPLICATECONTACTJOBTEST_H
