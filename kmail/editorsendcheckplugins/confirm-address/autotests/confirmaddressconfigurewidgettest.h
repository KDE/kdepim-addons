/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldLoadSaveResetValue();
};
