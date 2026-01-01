/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class AutogenerateConfigureAskWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskWidgetTest(QObject *parent = nullptr);
    ~AutogenerateConfigureAskWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
