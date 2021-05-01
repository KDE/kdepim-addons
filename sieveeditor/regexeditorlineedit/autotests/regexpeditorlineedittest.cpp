/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "regexpeditorlineedittest.h"
#include "../regexpeditorlineedit.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
#include <QToolButton>

RegexpEditorLineEditTest::RegexpEditorLineEditTest(QObject *parent)
    : QObject(parent)
{
}

void RegexpEditorLineEditTest::shouldHaveDefaultValue()
{
    RegexpEditorLineEdit w;

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    auto mRegExpEditorButton = w.findChild<QToolButton *>(QStringLiteral("regexpbutton"));
    QVERIFY(mRegExpEditorButton);
    QVERIFY(!mRegExpEditorButton->text().isEmpty());
    QVERIFY(!mRegExpEditorButton->toolTip().isEmpty());
}

QTEST_MAIN(RegexpEditorLineEditTest)
