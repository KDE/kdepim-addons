/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammalecteConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteConfigWidgetTest(QObject *parent = nullptr);
    ~GrammalecteConfigWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
