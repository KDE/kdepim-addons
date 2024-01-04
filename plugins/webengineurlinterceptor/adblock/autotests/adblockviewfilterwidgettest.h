/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockViewFilterWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockViewFilterWidgetTest(QObject *parent = nullptr);
    ~AdblockViewFilterWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
