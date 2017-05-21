/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "regexpeditorlineedittest.h"
#include "../regexpeditorlineedit.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

RegexpEditorLineEditTest::RegexpEditorLineEditTest(QObject *parent)
    : QObject(parent)
{

}

void RegexpEditorLineEditTest::shouldHaveDefaultValue()
{
    RegexpEditorLineEdit w;
    QLineEdit *mLineEdit = w.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    QPushButton *mRegExpEditorButton = w.findChild<QPushButton *>(QStringLiteral("regexpbutton"));
    QVERIFY(mRegExpEditorButton);
    QVERIFY(!mRegExpEditorButton->text().isEmpty());
    QVERIFY(!mRegExpEditorButton->toolTip().isEmpty());
}

QTEST_MAIN(RegexpEditorLineEditTest)
