/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidgettest.h"
#include "adblockfiltertreeview.h"
#include "adblockfilterwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AdblockFilterWidgetTest)

AdblockFilterWidgetTest::AdblockFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockFilterWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());

    auto mAdblockFilterListView = w.findChild<AdblockFilterTreeView *>(QStringLiteral("mAdblockFilterListView"));
    QVERIFY(mAdblockFilterListView);
}

#include "moc_adblockfilterwidgettest.cpp"
