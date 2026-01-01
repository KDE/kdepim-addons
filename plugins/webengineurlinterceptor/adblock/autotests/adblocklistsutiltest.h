/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockListsUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockListsUtilTest(QObject *parent = nullptr);
    ~AdblockListsUtilTest() override = default;
private Q_SLOTS:
    void shouldVerifyList();
};
