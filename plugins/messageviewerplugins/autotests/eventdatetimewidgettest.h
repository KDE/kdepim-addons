/*
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EVENTDATETIMEWIDGETTEST_H
#define EVENTDATETIMEWIDGETTEST_H
#include <QObject>

class EventDateTimeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit EventDateTimeWidgetTest(QObject *parent = nullptr);
    ~EventDateTimeWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSetDateTime();
    void shouldEmitSignalWhenDateTimeChanged();
    void shouldEmitSignalWhenJustTimeChanged();
    void shouldEmitSignalWhenJustDateChanged();
    void shouldNotEmitSignalWhenDateTimeWasNotChanged();
};

#endif // EVENTDATETIMEWIDGETTEST_H
