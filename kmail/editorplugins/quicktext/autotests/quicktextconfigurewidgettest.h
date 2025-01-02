/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class QuickTextConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextConfigureWidgetTest(QObject *parent = nullptr);
    ~QuickTextConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
