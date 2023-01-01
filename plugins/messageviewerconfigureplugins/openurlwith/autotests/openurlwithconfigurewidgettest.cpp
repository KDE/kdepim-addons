/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidgettest.h"
#include "openurlwithconfigurewidget.h"
#include <QListWidget>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureWidgetTest)
OpenUrlWithConfigureWidgetTest::OpenUrlWithConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mListWidget = w.findChild<QListWidget *>(QStringLiteral("mListWidget"));
    QVERIFY(mListWidget);
    QVERIFY(mListWidget->alternatingRowColors());
    QVERIFY(mListWidget->isSortingEnabled());
    QCOMPARE(mListWidget->contextMenuPolicy(), Qt::CustomContextMenu);
    QCOMPARE(mListWidget->selectionMode(), QAbstractItemView::ExtendedSelection);

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
