/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultwidgettest.h"
#include "languagetoolresultwidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <grammarresulttextedit.h>
QTEST_MAIN(LanguageToolResultWidgetTest)
LanguageToolResultWidgetTest::LanguageToolResultWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolResultWidgetTest::shouldHaveDefaultValue()
{
    LanguageToolResultWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<GrammarResultTextEdit *>(QStringLiteral("grammarResult"));
    QVERIFY(mResult);
}
