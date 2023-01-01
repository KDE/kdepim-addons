/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfigurewidgettest.h"
#include "../widgets/adblockpluginurlinterceptorconfigurewidget.h"
#include "../widgets/adblocksettingwidget.h"
#include <QTest>

AdblockPluginUrlInterceptorConfigureWidgetTest::AdblockPluginUrlInterceptorConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

AdblockPluginUrlInterceptorConfigureWidgetTest::~AdblockPluginUrlInterceptorConfigureWidgetTest() = default;

void AdblockPluginUrlInterceptorConfigureWidgetTest::shouldHaveDefaultValue()
{
    AdBlock::AdblockPluginUrlInterceptorConfigureWidget w;

    auto configurewidget = w.findChild<AdBlock::AdBlockSettingWidget *>(QStringLiteral("configurewidget"));
    QVERIFY(configurewidget);
}

QTEST_MAIN(AdblockPluginUrlInterceptorConfigureWidgetTest)
