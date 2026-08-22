/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapwidgettest.h"
#include "../selectimapwidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>

SelectImapWidgetTest::SelectImapWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

SelectImapWidgetTest::~SelectImapWidgetTest() = default;

void SelectImapWidgetTest::shouldHaveDefaultValue()
{
    SelectImapWidget w;
    const auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    const auto mToolButton = w.findChild<QToolButton *>(QStringLiteral("toolbutton"));
    QVERIFY(mToolButton);
    QVERIFY(!mToolButton->text().isEmpty());
}

void SelectImapWidgetTest::shouldAssignText()
{
    SelectImapWidget w;
    const auto mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QString text = QStringLiteral("foo");
    w.setText(text);
    QCOMPARE(w.text(), text);
    QCOMPARE(mLineEdit->text(), text);
    w.setText(QString());
    QVERIFY(w.text().isEmpty());
}

QTEST_MAIN(SelectImapWidgetTest)

#include "moc_selectimapwidgettest.cpp"
