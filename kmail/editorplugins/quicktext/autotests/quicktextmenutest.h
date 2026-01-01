/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class QuickTextMenuTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextMenuTest(QObject *parent = nullptr);
    ~QuickTextMenuTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
