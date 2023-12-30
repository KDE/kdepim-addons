/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockFilterListsViewTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockFilterListsViewTest(QObject *parent = nullptr);
    ~AdblockFilterListsViewTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
