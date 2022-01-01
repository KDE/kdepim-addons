/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class GrammarResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammarResultWidgetTest(QObject *parent = nullptr);
    ~GrammarResultWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

