/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidgettest.h"
#include "adblockfilterlistsview.h"
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

    auto mAdblockFilterListView = w.findChild<AdblockFilterListsView *>(QStringLiteral("mAdblockFilterListView"));
    QVERIFY(mAdblockFilterListView);
}

#include "moc_adblockfilterwidgettest.cpp"
