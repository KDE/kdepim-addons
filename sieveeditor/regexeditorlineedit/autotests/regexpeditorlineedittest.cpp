/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "regexpeditorlineedittest.h"
#include "../regexpeditorlineedit.h"
#include <QLineEdit>
#include <QToolButton>
#include <QTest>
#include <QHBoxLayout>

RegexpEditorLineEditTest::RegexpEditorLineEditTest(QObject *parent)
    : QObject(parent)
{
}

void RegexpEditorLineEditTest::shouldHaveDefaultValue()
{
    RegexpEditorLineEdit w;

    auto *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto *mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    auto *mRegExpEditorButton = w.findChild<QToolButton *>(QStringLiteral("regexpbutton"));
    QVERIFY(mRegExpEditorButton);
    QVERIFY(!mRegExpEditorButton->text().isEmpty());
    QVERIFY(!mRegExpEditorButton->toolTip().isEmpty());
}

QTEST_MAIN(RegexpEditorLineEditTest)
