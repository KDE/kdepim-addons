/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidgettest.h"
#include "openurlwithconfigurewidget.h"
#include <QListWidget>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureWidgetTest)
OpenUrlWithConfigureWidgetTest::OpenUrlWithConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void OpenUrlWithConfigureWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureWidget w;

    const auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mListWidget = w.findChild<QListWidget *>(QStringLiteral("mListWidget"));
    QVERIFY(mListWidget);
    QVERIFY(mListWidget->alternatingRowColors());
    QVERIFY(mListWidget->isSortingEnabled());
    QCOMPARE(mListWidget->contextMenuPolicy(), Qt::CustomContextMenu);
    QCOMPARE(mListWidget->selectionMode(), QAbstractItemView::ExtendedSelection);

    const auto mAddRule = w.findChild<QPushButton *>(QStringLiteral("mAddRule"));
    QVERIFY(mAddRule);
    QVERIFY(!mAddRule->text().isEmpty());

    const auto mRemoveRule = w.findChild<QPushButton *>(QStringLiteral("mRemoveRule"));
    QVERIFY(mRemoveRule);
    QVERIFY(!mRemoveRule->text().isEmpty());

    const auto mModifyRule = w.findChild<QPushButton *>(QStringLiteral("mModifyRule"));
    QVERIFY(mModifyRule);
    QVERIFY(!mModifyRule->text().isEmpty());
}

#include "moc_openurlwithconfigurewidgettest.cpp"
