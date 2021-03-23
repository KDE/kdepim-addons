/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressConfigureTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureTabWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

