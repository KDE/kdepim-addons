/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QObject>

class EventDateTimeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit EventDateTimeWidgetTest(QObject *parent = nullptr);
    ~EventDateTimeWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSetDateTime();
    void shouldEmitSignalWhenDateTimeChanged();
    void shouldEmitSignalWhenJustTimeChanged();
    void shouldEmitSignalWhenJustDateChanged();
    void shouldNotEmitSignalWhenDateTimeWasNotChanged();
};
