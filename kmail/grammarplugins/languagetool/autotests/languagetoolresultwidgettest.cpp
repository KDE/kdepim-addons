/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
