/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptortest.h"
#include "../adblockpluginurlinterceptor.h"
#include <QTest>
#include <QWebEngineView>

AdblockPluginUrlInterceptorTest::AdblockPluginUrlInterceptorTest(QObject *parent)
    : QObject(parent)
{
}

AdblockPluginUrlInterceptorTest::~AdblockPluginUrlInterceptorTest() = default;

void AdblockPluginUrlInterceptorTest::shouldHaveDefaultValue()
{
    AdblockPluginUrlInterceptor w;
    QVERIFY(w.createInterface(new QWebEngineView(), this));
    QVERIFY(w.hasConfigureDialog());
}

QTEST_MAIN(AdblockPluginUrlInterceptorTest)
