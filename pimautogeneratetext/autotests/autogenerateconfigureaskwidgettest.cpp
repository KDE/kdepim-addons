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
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(AutogenerateConfigureAskWidgetTest)

AutogenerateConfigureAskWidgetTest::AutogenerateConfigureAskWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureAskWidgetTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskWidget w;

    const auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    const auto mSplitter = w.findChild<QSplitter *>(u"mSplitter"_s);
    QVERIFY(mSplitter);

    const auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);

    const auto mTextEdit = w.findChild<QPlainTextEdit *>(u"mTextEdit"_s);
    QVERIFY(mTextEdit);

    const auto mAutogenerateConfigureListView = w.findChild<AutogenerateConfigureListView *>(u"mAutogenerateConfigureListView"_s);
    QVERIFY(mAutogenerateConfigureListView);
}

#include "moc_autogenerateconfigureaskwidgettest.cpp"
