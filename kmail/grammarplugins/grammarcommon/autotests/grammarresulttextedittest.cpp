/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresulttextedittest.h"
#include "grammarresulttextedit.h"
#include <QTest>
#include <QStandardPaths>
QTEST_MAIN(GrammarResultTextEditTest)

GrammarResultTextEditTest::GrammarResultTextEditTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammarResultTextEditTest::shouldHaveDefaultValue()
{
    GrammarResultTextEdit w;
    QVERIFY(w.isReadOnly());
    QVERIFY(!w.acceptRichText());
}
