/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockFilterDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockFilterDialogTest(QObject *parent = nullptr);
    ~AdblockFilterDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
