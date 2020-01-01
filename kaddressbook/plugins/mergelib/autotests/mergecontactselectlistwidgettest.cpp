/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "mergecontactselectlistwidgettest.h"
#include "job/mergecontacts.h"
#include "widgets/mergecontactselectlistwidget.h"
#include <QListWidget>
#include <QLabel>
#include <QTest>

MergeContactSelectListWidgetTest::MergeContactSelectListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectListWidgetTest::~MergeContactSelectListWidgetTest()
{
}

void MergeContactSelectListWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectListWidget selectListWidget;

    QLabel *title = selectListWidget.findChild<QLabel *>(QStringLiteral("title"));
    QVERIFY(title);
    QListWidget *listWidget = selectListWidget.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(selectListWidget.selectedContact(), -1);
    QCOMPARE(selectListWidget.conflictType(), KABMergeContacts::MergeContacts::None);
}

QTEST_MAIN(MergeContactSelectListWidgetTest)
