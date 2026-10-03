/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "donottrackpluginurlinterceptortest.h"
#include "../donottrackpluginurlinterceptor.h"
#include <QTest>
#include <QWebEngineView>
DoNotTrackPluginUrlInterceptorTest::DoNotTrackPluginUrlInterceptorTest(QObject *parent)
    : QObject(parent)
{
}

DoNotTrackPluginUrlInterceptorTest::~DoNotTrackPluginUrlInterceptorTest() = default;

void DoNotTrackPluginUrlInterceptorTest::shouldHaveDefaultValue()
{
    DoNotTrackPluginUrlInterceptor w;

    auto view = std::make_unique<QWebEngineView>();
    QVERIFY(w.createInterface(view.get(), this));
}

QTEST_MAIN(DoNotTrackPluginUrlInterceptorTest)

#include "moc_donottrackpluginurlinterceptortest.cpp"
