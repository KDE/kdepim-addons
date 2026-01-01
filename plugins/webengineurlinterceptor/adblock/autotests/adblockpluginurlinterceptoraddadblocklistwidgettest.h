/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class AdblockPluginUrlInterceptorAddAdblockListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorAddAdblockListWidgetTest(QObject *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldVerifyAdBlockListInfo();
};
