/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertShorturlConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureWidgetTest(QObject *parent = nullptr);
    ~InsertShorturlConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

