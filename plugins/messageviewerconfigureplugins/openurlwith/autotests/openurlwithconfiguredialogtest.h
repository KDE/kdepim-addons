/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OpenUrlWithConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureDialogTest(QObject *parent = nullptr);
    ~OpenUrlWithConfigureDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
