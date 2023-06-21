/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactwidgetlisttest.h"
#include "../manualmerge/mergecontactwidgetlist.h"
#include <Akonadi/Item>
#include <QTest>
using namespace KContacts;

MergeContactWidgetListTest::MergeContactWidgetListTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactWidgetListTest::~MergeContactWidgetListTest() = default;

void MergeContactWidgetListTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactWidgetList w;
    QCOMPARE(w.count(), 0);
}

void MergeContactWidgetListTest::shouldCleanListWhenSetItems()
{
    KABMergeContacts::MergeContactWidgetList w;
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    lst << Akonadi::Item(42);
    w.fillListContact(lst);
    // We don't have KABC::Address
    QCOMPARE(w.count(), 0);

    Addressee address;
    Akonadi::Item item;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<Addressee>(address);
    lst << item;
    w.fillListContact(lst);
    QCOMPARE(w.count(), 1);

    // it must clear;
    w.fillListContact(lst);
    QCOMPARE(w.count(), 1);
}

QTEST_MAIN(MergeContactWidgetListTest)

#include "moc_mergecontactwidgetlisttest.cpp"
