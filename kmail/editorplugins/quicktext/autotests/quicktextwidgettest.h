/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class QuickTextWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextWidgetTest(QObject *parent = nullptr);
    ~QuickTextWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
