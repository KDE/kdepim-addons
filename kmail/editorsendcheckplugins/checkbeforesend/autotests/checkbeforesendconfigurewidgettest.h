/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CheckBeforeSendConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureWidgetTest(QObject *parent = nullptr);
    ~CheckBeforeSendConfigureWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldResetValue();
};
