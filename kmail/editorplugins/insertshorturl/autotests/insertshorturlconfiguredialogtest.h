/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertShorturlConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureDialogTest(QObject *parent = nullptr);
    ~InsertShorturlConfigureDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
