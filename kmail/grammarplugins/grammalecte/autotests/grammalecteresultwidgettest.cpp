/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultwidgettest.h"
#include "grammalecteresultwidget.h"
#include "grammarresulttextedit.h"
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(GrammarResultWidgetTest)

GrammarResultWidgetTest::GrammarResultWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void GrammarResultWidgetTest::shouldHaveDefaultValue()
{
    GrammalecteResultWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<GrammarResultTextEdit *>(QStringLiteral("grammarResult"));
    QVERIFY(mResult);

    auto closeBtn = w.findChild<QToolButton *>(QStringLiteral("close-button"));
    QVERIFY(closeBtn);
    QVERIFY(!closeBtn->icon().isNull());
    QVERIFY(!closeBtn->toolTip().isEmpty());
}
