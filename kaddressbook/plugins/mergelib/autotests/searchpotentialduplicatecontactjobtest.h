/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
