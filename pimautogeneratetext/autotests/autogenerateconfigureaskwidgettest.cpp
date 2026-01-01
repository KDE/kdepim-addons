/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskwidgettest.h"
#include "autogenerateconfigureaskwidget.h"
#include "autogenerateconfigurelistview.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QTest>

QTEST_MAIN(AutogenerateConfigureAskWidgetTest)

AutogenerateConfigureAskWidgetTest::AutogenerateConfigureAskWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureAskWidgetTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSplitter = w.findChild<QSplitter *>(QStringLiteral("mSplitter"));
    QVERIFY(mSplitter);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);

    auto mTextEdit = w.findChild<QPlainTextEdit *>(QStringLiteral("mTextEdit"));
    QVERIFY(mTextEdit);

    auto mAutogenerateConfigureListView = w.findChild<AutogenerateConfigureListView *>(QStringLiteral("mAutogenerateConfigureListView"));
    QVERIFY(mAutogenerateConfigureListView);
}

#include "moc_autogenerateconfigureaskwidgettest.cpp"
