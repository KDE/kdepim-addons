/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressPluginTest(QObject *parent = nullptr);
    ~ConfirmAddressPluginTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
