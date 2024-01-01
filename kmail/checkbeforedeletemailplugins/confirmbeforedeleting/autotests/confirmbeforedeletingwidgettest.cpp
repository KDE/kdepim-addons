/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidgettest.h"
#include "confirmbeforedeletingwidget.h"
#include <QPushButton>
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

    auto mAddRule = w.findChild<QPushButton *>(QStringLiteral("mAddRule"));
    QVERIFY(mAddRule);
    QVERIFY(!mAddRule->text().isEmpty());

    auto mRemoveRule = w.findChild<QPushButton *>(QStringLiteral("mRemoveRule"));
    QVERIFY(mRemoveRule);
    QVERIFY(!mRemoveRule->text().isEmpty());

    auto mModifyRule = w.findChild<QPushButton *>(QStringLiteral("mModifyRule"));
    QVERIFY(mModifyRule);
    QVERIFY(!mModifyRule->text().isEmpty());
}

#include "moc_confirmbeforedeletingwidgettest.cpp"
