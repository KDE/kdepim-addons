/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddAddress();
    void shouldAddValidAndInvalidAddresses();
    void shouldHaveCheckableItem();
    void shouldGetWhileListEmails();
};
