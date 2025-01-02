/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ConfirmAddressEmailEntryDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressEmailEntryDialogTest(QObject *parent = nullptr);
    ~ConfirmAddressEmailEntryDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
