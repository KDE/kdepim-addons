/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimmanageruleswidgettest.h"
#include "dkimmanageruleswidget.h"

#include <KTreeWidgetSearchLine>

#include <QTest>
#include <QTreeWidget>
#include <QVBoxLayout>

QTEST_MAIN(DKIMManageRulesWidgetTest)

DKIMManageRulesWidgetTest::DKIMManageRulesWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMManageRulesWidgetTest::shouldHaveDefaultValues()
{
    DKIMManageRulesWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QTreeWidget *mTreeWidget = w.findChild<QTreeWidget *>(QStringLiteral("treewidget"));
    QVERIFY(mTreeWidget);
    QVERIFY(!mTreeWidget->rootIsDecorated());
    QVERIFY(mTreeWidget->alternatingRowColors());

    KTreeWidgetSearchLine *searchLineEdit = w.findChild<KTreeWidgetSearchLine *>(QStringLiteral("searchlineedit"));
    QVERIFY(searchLineEdit->isClearButtonEnabled());
}
