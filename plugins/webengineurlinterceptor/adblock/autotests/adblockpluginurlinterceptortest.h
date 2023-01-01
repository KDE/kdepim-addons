/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockPluginUrlInterceptorTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorTest(QObject *parent = nullptr);
    ~AdblockPluginUrlInterceptorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
