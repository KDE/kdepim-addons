/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

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
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    GrammarResultTextEdit *mResult = w.findChild<GrammarResultTextEdit *>(QStringLiteral("grammarResult"));
    QVERIFY(mResult);
}
