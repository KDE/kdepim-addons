/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKBEFORESENDCONFIGUREWIDGETTEST_H
#define CHECKBEFORESENDCONFIGUREWIDGETTEST_H

#include <QObject>

class CheckBeforeSendConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureWidgetTest(QObject *parent = nullptr);
    ~CheckBeforeSendConfigureWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldResetValue();
};

#endif // CHECKBEFORESENDCONFIGUREWIDGETTEST_H
