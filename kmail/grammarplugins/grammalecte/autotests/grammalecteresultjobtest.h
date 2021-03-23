/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammarResultJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultJobTest(QObject *parent = nullptr);
    ~GrammarResultJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};

