/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressConfigureTabTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureTabTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
