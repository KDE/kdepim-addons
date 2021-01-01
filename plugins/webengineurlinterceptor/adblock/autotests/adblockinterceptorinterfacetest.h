/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKINTERCEPTORINTERFACETEST_H
#define ADBLOCKINTERCEPTORINTERFACETEST_H

#include <QObject>

class AdblockInterceptorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockInterceptorInterfaceTest(QObject *parent = nullptr);
    ~AdblockInterceptorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // ADBLOCKINTERCEPTORINTERFACETEST_H
