/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockpluginurlinterceptoraddadblocklistwidgettest.h"
#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(AdblockPluginUrlInterceptorAddAdblockListWidgetTest)

AdblockPluginUrlInterceptorAddAdblockListWidgetTest::AdblockPluginUrlInterceptorAddAdblockListWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockPluginUrlInterceptorAddAdblockListWidgetTest::shouldHaveDefaultValues()
{
    AdblockPluginUrlInterceptorAddAdblockListWidget w;

    const auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    const auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    const auto mUrl = w.findChild<QLineEdit *>(u"mUrl"_s);
    QVERIFY(mUrl);
    QVERIFY(mUrl->text().isEmpty());
}

void AdblockPluginUrlInterceptorAddAdblockListWidgetTest::shouldVerifyAdBlockListInfo()
{
    AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info;
    QVERIFY(!info.isValid());

    info.name = u"bla"_s;
    QVERIFY(!info.isValid());

    info.url = u"bli"_s;
    QVERIFY(info.isValid());

    info.name.clear();
    QVERIFY(!info.isValid());
}

#include "moc_adblockpluginurlinterceptoraddadblocklistwidgettest.cpp"
