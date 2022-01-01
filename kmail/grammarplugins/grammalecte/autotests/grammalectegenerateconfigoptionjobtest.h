/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammalecteGenerateConfigOptionJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteGenerateConfigOptionJobTest(QObject *parent = nullptr);
    ~GrammalecteGenerateConfigOptionJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};

