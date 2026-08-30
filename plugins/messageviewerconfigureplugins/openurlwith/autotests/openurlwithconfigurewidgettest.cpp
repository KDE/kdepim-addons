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
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(OpenUrlWithConfigureWidgetTest)
OpenUrlWithConfigureWidgetTest::OpenUrlWithConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void OpenUrlWithConfigureWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureWidget w;

    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mListWidget = w.findChild<QListWidget *>(u"mListWidget"_s);
    QVERIFY(mListWidget);
    QVERIFY(mListWidget->alternatingRowColors());
    QVERIFY(mListWidget->isSortingEnabled());
    QCOMPARE(mListWidget->contextMenuPolicy(), Qt::CustomContextMenu);
    QCOMPARE(mListWidget->selectionMode(), QAbstractItemView::ExtendedSelection);

    const auto mAddRule = w.findChild<QPushButton *>(u"mAddRule"_s);
    QVERIFY(mAddRule);
    QVERIFY(!mAddRule->text().isEmpty());

    const auto mRemoveRule = w.findChild<QPushButton *>(u"mRemoveRule"_s);
    QVERIFY(mRemoveRule);
    QVERIFY(!mRemoveRule->text().isEmpty());

    const auto mModifyRule = w.findChild<QPushButton *>(u"mModifyRule"_s);
    QVERIFY(mModifyRule);
    QVERIFY(!mModifyRule->text().isEmpty());
}

#include "moc_openurlwithconfigurewidgettest.cpp"
