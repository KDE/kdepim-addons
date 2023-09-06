/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockFilterWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockFilterWidgetTest(QObject *parent = nullptr);
    ~AdblockFilterWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
