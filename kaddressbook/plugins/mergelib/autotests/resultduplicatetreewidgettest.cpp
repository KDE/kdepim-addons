/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "resultduplicatetreewidgettest.h"
#include "../searchduplicate/resultduplicatetreewidget.h"
#include <KContacts/Addressee>
#include <QTest>

using namespace KContacts;

ResultDuplicateTreeWidgetTest::ResultDuplicateTreeWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ResultDuplicateTreeWidgetTest::~ResultDuplicateTreeWidgetTest() = default;

void ResultDuplicateTreeWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    QCOMPARE(w.topLevelItemCount(), 0);
}

void ResultDuplicateTreeWidgetTest::shouldFillList()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    w.setContacts(itemLst);
    QCOMPARE(w.topLevelItemCount(), 1);
}

void ResultDuplicateTreeWidgetTest::shouldClearList()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    w.setContacts(itemLst);

    Akonadi::Item item(45);
    Addressee address;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<Addressee>(address);
    lst << item;
    itemLst.clear();
    itemLst << lst;
    w.setContacts(itemLst);
    QCOMPARE(w.topLevelItemCount(), 1);
}

void ResultDuplicateTreeWidgetTest::shouldEmptyListIfNotContactSelected()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    Akonadi::Item item(45);
    Addressee address;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<Addressee>(address);
    lst << item;
    itemLst << lst;
    w.setContacts(itemLst);
    QVERIFY(w.selectedContactsToMerge().isEmpty());
}

void ResultDuplicateTreeWidgetTest::shouldReturnNotEmptyContactList()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    w.setContacts(itemLst);

    for (int i = 0; i < w.topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = w.topLevelItem(i);
        const int childCount = item->childCount();
        if (childCount > 0) {
            for (int child = 0; child < childCount; ++child) {
                auto childItem = static_cast<KABMergeContacts::ResultDuplicateTreeWidgetItem *>(item->child(child));
                childItem->setCheckState(0, Qt::Checked);
            }
        }
    }
    QCOMPARE(w.selectedContactsToMerge().count(), 1);
}

void ResultDuplicateTreeWidgetTest::shouldNotReturnListWhenJustOneChildSelected()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    w.setContacts(itemLst);

    for (int i = 0; i < w.topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = w.topLevelItem(i);
        const int childCount = item->childCount();
        if (childCount > 0) {
            for (int child = 0; child < childCount; ++child) {
                auto childItem = static_cast<KABMergeContacts::ResultDuplicateTreeWidgetItem *>(item->child(child));
                childItem->setCheckState(0, child == 0 ? Qt::Checked : Qt::Unchecked);
            }
        }
    }
    QCOMPARE(w.selectedContactsToMerge().count(), 0);
}

void ResultDuplicateTreeWidgetTest::shouldReturnTwoLists()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    itemLst << lst;
    w.setContacts(itemLst);

    for (int i = 0; i < w.topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = w.topLevelItem(i);
        const int childCount = item->childCount();
        if (childCount > 0) {
            for (int child = 0; child < childCount; ++child) {
                auto childItem = static_cast<KABMergeContacts::ResultDuplicateTreeWidgetItem *>(item->child(child));
                childItem->setCheckState(0, Qt::Checked);
                QVERIFY(childItem->item().isValid());
            }
        }
    }
    QCOMPARE(w.selectedContactsToMerge().count(), 2);
}

void ResultDuplicateTreeWidgetTest::shouldReturnJustOnList()
{
    KABMergeContacts::ResultDuplicateTreeWidget w;
    Akonadi::Item::List lst;
    for (int i = 0; i < 5; ++i) {
        Akonadi::Item item(42 + i);
        Addressee address;
        address.setName(QStringLiteral("foo1"));
        item.setPayload<Addressee>(address);
        lst << item;
    }
    QList<Akonadi::Item::List> itemLst;
    itemLst << lst;
    itemLst << lst;
    w.setContacts(itemLst);

    bool firstList = true;
    for (int i = 0; i < w.topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = w.topLevelItem(i);
        const int childCount = item->childCount();
        if (childCount > 0) {
            for (int child = 0; child < childCount; ++child) {
                auto childItem = static_cast<KABMergeContacts::ResultDuplicateTreeWidgetItem *>(item->child(child));
                childItem->setCheckState(0, firstList ? Qt::Checked : Qt::Unchecked);
            }
        }
        firstList = false;
    }
    QCOMPARE(w.selectedContactsToMerge().count(), 1);
}

QTEST_MAIN(ResultDuplicateTreeWidgetTest)

#include "moc_resultduplicatetreewidgettest.cpp"
