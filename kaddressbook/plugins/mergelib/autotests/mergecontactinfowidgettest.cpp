/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactinfowidgettest.h"

#include "widgets/mergecontactinfowidget.h"
#include <QStackedWidget>
#include <QStandardPaths>
#include <QTest>
using namespace KABMergeContacts;

MergeContactInfoWidgetTest::MergeContactInfoWidgetTest() = default;

void MergeContactInfoWidgetTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void MergeContactInfoWidgetTest::shouldHaveDefaultValueOnCreation()
{
    MergeContactInfoWidget infoWidget;
    auto stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontact"));
}

void MergeContactInfoWidgetTest::shouldHaveActivateDisplayWidgetWhenSelectOneContact()
{
    MergeContactInfoWidget infoWidget;
    Akonadi::Item item(4);
    infoWidget.setContact(item);
    auto stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("contactwidget"));
}

void MergeContactInfoWidgetTest::shouldHaveActivateNoWidgetWhenSelectNoContact()
{
    MergeContactInfoWidget infoWidget;
    Akonadi::Item item(4);
    infoWidget.setContact(item);
    auto stackedWidget = infoWidget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("contactwidget"));
    infoWidget.setContact(Akonadi::Item());
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontact"));
}

QTEST_MAIN(MergeContactInfoWidgetTest)

#include "moc_mergecontactinfowidgettest.cpp"
