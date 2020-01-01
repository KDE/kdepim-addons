/*
   Copyright (C) 2014-2020 Laurent Montel <montel@kde.org>

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

#include "mergecontactinfowidgettest.h"

#include <QTest>
#include "widgets/mergecontactinfowidget.h"
#include <QStackedWidget>
#include <QStandardPaths>
using namespace KABMergeContacts;

MergeContactInfoWidgetTest::MergeContactInfoWidgetTest()
{
}

void MergeContactInfoWidgetTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void MergeContactInfoWidgetTest::shouldHaveDefaultValueOnCreation()
{
    MergeContactInfoWidget infoWidget;
    QStackedWidget *stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontact"));
}

void MergeContactInfoWidgetTest::shouldHaveActivateDisplayWidgetWhenSelectOneContact()
{
    MergeContactInfoWidget infoWidget;
    Akonadi::Item item(4);
    infoWidget.setContact(item);
    QStackedWidget *stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("contactwidget"));
}

void MergeContactInfoWidgetTest::shouldHaveActivateNoWidgetWhenSelectNoContact()
{
    MergeContactInfoWidget infoWidget;
    Akonadi::Item item(4);
    infoWidget.setContact(item);
    QStackedWidget *stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("contactwidget"));
    infoWidget.setContact(Akonadi::Item());
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontact"));
}

QTEST_MAIN(MergeContactInfoWidgetTest)
