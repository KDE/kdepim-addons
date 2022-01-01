/*
   SPDX-FileCopyrightText: 2021-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidgettest.h"
#include "confirmbeforedeletingwidget.h"
#include <QTest>
#include <QTreeWidget>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingWidgetTest)

ConfirmBeforeDeletingWidgetTest::ConfirmBeforeDeletingWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingWidgetTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTreeWidget = w.findChild<QTreeWidget *>(QStringLiteral("mTreeWidget"));
    QVERIFY(mTreeWidget->alternatingRowColors());
    QVERIFY(!mTreeWidget->rootIsDecorated());
    QCOMPARE(mTreeWidget->contextMenuPolicy(), Qt::CustomContextMenu);
}
