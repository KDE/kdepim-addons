/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidgettest.h"
#include "openurlwithconfigurewidget.h"
#include <QListWidget>
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
}
