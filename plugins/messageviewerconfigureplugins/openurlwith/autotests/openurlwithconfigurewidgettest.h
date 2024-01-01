/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OpenUrlWithConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureWidgetTest(QObject *parent = nullptr);
    ~OpenUrlWithConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
