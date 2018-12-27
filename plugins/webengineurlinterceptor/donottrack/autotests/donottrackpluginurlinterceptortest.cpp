/*
    Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "donottrackpluginurlinterceptortest.h"
#include "../donottrackpluginurlinterceptor.h"
#include <QTest>
#include <QWebEngineView>
DoNotTrackPluginUrlInterceptorTest::DoNotTrackPluginUrlInterceptorTest(QObject *parent)
    : QObject(parent)
{
}

DoNotTrackPluginUrlInterceptorTest::~DoNotTrackPluginUrlInterceptorTest()
{
}

void DoNotTrackPluginUrlInterceptorTest::shouldHaveDefaultValue()
{
    DoNotTrackPluginUrlInterceptor w;

    QVERIFY(w.createInterface(new QWebEngineView(), this));
}

QTEST_MAIN(DoNotTrackPluginUrlInterceptorTest)
