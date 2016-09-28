/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalconfigurewidgettest.h"
#include "../configuredialog/viewerpluginexternalconfigurewidget.h"
#include <QTest>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

ViewerPluginExternalConfigureWidgetTest::ViewerPluginExternalConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{

}

ViewerPluginExternalConfigureWidgetTest::~ViewerPluginExternalConfigureWidgetTest()
{

}

void ViewerPluginExternalConfigureWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalConfigureWidget w;
    QLabel *label = w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(label);
    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("layout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->margin(), 0);

    QListWidget *mListExternal = w.findChild<QListWidget *>(QStringLiteral("listexternal"));
    QVERIFY(mListExternal);
    QCOMPARE(mListExternal->selectionMode(), QAbstractItemView::SingleSelection);

    QPushButton *mAddScript = w.findChild<QPushButton *>(QStringLiteral("addscript"));
    QVERIFY(mAddScript);
    QVERIFY(!mAddScript->text().isEmpty());

    QPushButton *mModifyScript = w.findChild<QPushButton *>(QStringLiteral("modifyscript"));
    QVERIFY(mModifyScript);
    QVERIFY(!mModifyScript->text().isEmpty());

    QPushButton *mRemoveScript = w.findChild<QPushButton *>(QStringLiteral("removescript"));
    QVERIFY(mRemoveScript);
    QVERIFY(!mRemoveScript->text().isEmpty());
}

QTEST_MAIN(ViewerPluginExternalConfigureWidgetTest)
