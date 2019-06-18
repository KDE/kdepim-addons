/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "selectimapwidgettest.h"
#include "../selectimapwidget.h"
#include "kdepimtest_layout.h"

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
    KdepimTestLayout::checkContentsMargins(0, mainLayout);
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
