/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DelegateSelectorTest : public QObject
{
    Q_OBJECT
public:
    explicit DelegateSelectorTest(QObject *parent = nullptr);
    ~DelegateSelectorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeOkButtonState();
    void shouldReturnCheckBoxState();
};

