/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammarResultTextEditTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultTextEditTest(QObject *parent = nullptr);
    ~GrammarResultTextEditTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
