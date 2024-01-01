/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationtabwidgettest.h"
#include "../searchduplicate/mergecontactselectinformationtabwidget.h"
#include <QTest>

MergeContactSelectInformationTabWidgetTest::MergeContactSelectInformationTabWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationTabWidgetTest::~MergeContactSelectInformationTabWidgetTest() = default;

void MergeContactSelectInformationTabWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationTabWidget w;
    QVERIFY(!w.tabBarVisible());
    QCOMPARE(w.count(), 0);
}

void MergeContactSelectInformationTabWidgetTest::shouldAddTab()
{
    KABMergeContacts::MergeContactSelectInformationTabWidget w;

    QList<KABMergeContacts::MergeConflictResult> list;
    KABMergeContacts::MergeConflictResult conflict;
    Akonadi::Item::List listItem;
    KContacts::Addressee address1;
    Akonadi::Item item1;
    address1.setName(QStringLiteral("foo1"));
    item1.setPayload<KContacts::Addressee>(address1);

    KContacts::Addressee address2;
    Akonadi::Item item2;
    address2.setName(QStringLiteral("foo2"));
    item2.setPayload<KContacts::Addressee>(address2);

    listItem << item1;
    listItem << item2;

    KABMergeContacts::MergeContacts::ConflictInformations conflictInformation = KABMergeContacts::MergeContacts::Birthday;
    conflict.list = listItem;
    conflict.conflictInformation = conflictInformation;

    list << conflict;
    w.setRequiresSelectInformationWidgets(list, Akonadi::Collection(42));
    QVERIFY(!w.tabBarVisible());
    QCOMPARE(w.count(), 1);

    list << conflict;
    w.setRequiresSelectInformationWidgets(list, Akonadi::Collection(42));
    QVERIFY(!w.tabBarVisible());
    QCOMPARE(w.count(), 2);
}

QTEST_MAIN(MergeContactSelectInformationTabWidgetTest)

#include "moc_mergecontactselectinformationtabwidgettest.cpp"
