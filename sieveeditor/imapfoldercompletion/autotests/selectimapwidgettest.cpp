/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapwidgettest.h"
#include "../selectimapwidget.h"

#include <QTest>
#include <QHBoxLayout>
#include <QToolButton>
#include <QLineEdit>

SelectImapWidgetTest::SelectImapWidgetTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapWidgetTest::~SelectImapWidgetTest()
{
}

void SelectImapWidgetTest::shouldHaveDefaultValue()
{
    SelectImapWidget w;
    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QLineEdit *mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    QToolButton *mToolButton = w.findChild<QToolButton *>(QStringLiteral("toolbutton"));
    QVERIFY(mToolButton);
    QVERIFY(!mToolButton->text().isEmpty());
}

void SelectImapWidgetTest::shouldAssignText()
{
    SelectImapWidget w;
    QLineEdit *mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QString text = QStringLiteral("foo");
    w.setText(text);
    QCOMPARE(w.text(), text);
    QCOMPARE(mLineEdit->text(), text);
    w.setText(QString());
    QVERIFY(w.text().isEmpty());
}

QTEST_MAIN(SelectImapWidgetTest)
