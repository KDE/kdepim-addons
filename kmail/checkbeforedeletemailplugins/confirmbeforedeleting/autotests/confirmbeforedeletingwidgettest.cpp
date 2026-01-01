/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTreeWidget = w.findChild<QTreeWidget *>(u"mTreeWidget"_s);
    QVERIFY(mTreeWidget->alternatingRowColors());
    QVERIFY(!mTreeWidget->rootIsDecorated());
    QCOMPARE(mTreeWidget->contextMenuPolicy(), Qt::CustomContextMenu);

    auto mAddRule = w.findChild<QPushButton *>(u"mAddRule"_s);
    QVERIFY(mAddRule);
    QVERIFY(!mAddRule->text().isEmpty());

    auto mRemoveRule = w.findChild<QPushButton *>(u"mRemoveRule"_s);
    QVERIFY(mRemoveRule);
    QVERIFY(!mRemoveRule->text().isEmpty());

    auto mModifyRule = w.findChild<QPushButton *>(u"mModifyRule"_s);
    QVERIFY(mModifyRule);
    QVERIFY(!mModifyRule->text().isEmpty());
}

#include "moc_confirmbeforedeletingwidgettest.cpp"
