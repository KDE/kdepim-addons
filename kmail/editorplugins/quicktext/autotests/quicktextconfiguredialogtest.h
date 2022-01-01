/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class QuickTextConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextConfigureDialogTest(QObject *parent = nullptr);
    ~QuickTextConfigureDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

