/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockpluginurlinterceptoraddadblocklistwidgettest.h"
#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(AdblockPluginUrlInterceptorAddAdblockListWidgetTest)

AdblockPluginUrlInterceptorAddAdblockListWidgetTest::AdblockPluginUrlInterceptorAddAdblockListWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockPluginUrlInterceptorAddAdblockListWidgetTest::shouldHaveDefaultValues()
{
    AdblockPluginUrlInterceptorAddAdblockListWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(QStringLiteral("mName"));
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    auto mUrl = w.findChild<QLineEdit *>(QStringLiteral("mUrl"));
    QVERIFY(mUrl);
    QVERIFY(mUrl->text().isEmpty());
}

#include "moc_adblockpluginurlinterceptoraddadblocklistwidgettest.cpp"
