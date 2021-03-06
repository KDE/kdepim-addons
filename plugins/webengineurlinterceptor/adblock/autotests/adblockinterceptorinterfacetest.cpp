/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockinterceptorinterfacetest.h"
#include "../adblockinterceptorinterface.h"
#include <QTest>

AdblockInterceptorInterfaceTest::AdblockInterceptorInterfaceTest(QObject *parent)
    : QObject(parent)
{
}

AdblockInterceptorInterfaceTest::~AdblockInterceptorInterfaceTest()
{
}

void AdblockInterceptorInterfaceTest::shouldHaveDefaultValue()
{
    AdblockInterceptorInterface w;
    QVERIFY(!w.webEngineView());
}

QTEST_MAIN(AdblockInterceptorInterfaceTest)
