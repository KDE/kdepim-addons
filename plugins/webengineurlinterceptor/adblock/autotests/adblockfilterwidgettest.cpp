/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidgettest.h"
#include "adblockfiltertreeview.h"
#include "adblockfilterwidget.h"
#include <QLineEdit>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(AdblockFilterWidgetTest)

AdblockFilterWidgetTest::AdblockFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AdblockFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockFilterWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    const auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());

    const auto mAdblockFilterListView = w.findChild<AdblockFilterTreeView *>(u"mAdblockFilterListView"_s);
    QVERIFY(mAdblockFilterListView);
}

#include "moc_adblockfilterwidgettest.cpp"
