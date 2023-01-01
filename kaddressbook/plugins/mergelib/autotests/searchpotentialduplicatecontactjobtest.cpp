/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchpotentialduplicatecontactjobtest.h"
#include "../job/searchpotentialduplicatecontactjob.h"

#include <Akonadi/Item>
#include <KContacts/Addressee>
#include <QSignalSpy>
#include <QTest>

using namespace KABMergeContacts;
SearchPotentialDuplicateContactJobTest::SearchPotentialDuplicateContactJobTest()
{
    qRegisterMetaType<QVector<Akonadi::Item>>();
    qRegisterMetaType<QVector<Akonadi::Item::List>>();
}

void SearchPotentialDuplicateContactJobTest::shouldReturnEmptyListWhenNoItem()
{
    Akonadi::Item::List lst;
    SearchPotentialDuplicateContactJob job(lst);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), 0);
}

void SearchPotentialDuplicateContactJobTest::shouldReturnEmptyListWhenOneItem()
{
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    SearchPotentialDuplicateContactJob job(lst);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), 0);
}

void SearchPotentialDuplicateContactJobTest::shouldReturnListWhenTwoItemsAreDuplicated()
{
    Akonadi::Item::List lst;
    Akonadi::Item itemA;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    itemA.setPayload<KContacts::Addressee>(address);
    itemA.setMimeType(KContacts::Addressee::mimeType());

    lst << itemA << itemA;

    SearchPotentialDuplicateContactJob job(lst);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), 1);
}

void SearchPotentialDuplicateContactJobTest::shouldReturnListWhenThreeItemsAreDuplicated()
{
    Akonadi::Item::List lst;
    Akonadi::Item itemA;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    itemA.setPayload<KContacts::Addressee>(address);
    itemA.setMimeType(KContacts::Addressee::mimeType());

    lst << itemA << itemA << itemA;

    SearchPotentialDuplicateContactJob job(lst);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), 1);
}

void SearchPotentialDuplicateContactJobTest::shouldReturnTwoList()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee addressA;
    addressA.setName(QStringLiteral("foo1"));
    item.setPayload<KContacts::Addressee>(addressA);
    item.setMimeType(KContacts::Addressee::mimeType());

    lst << item << item << item;

    KContacts::Addressee addressB;
    addressB.setName(QStringLiteral("foo2"));
    item.setPayload<KContacts::Addressee>(addressB);
    item.setMimeType(KContacts::Addressee::mimeType());

    lst << item << item << item;

    SearchPotentialDuplicateContactJob job(lst);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), 2);
}

void SearchPotentialDuplicateContactJobTest::shouldReturnList_data()
{
    QTest::addColumn<Akonadi::Item::List>("listItem");
    QTest::addColumn<int>("numberOfList");
    QTest::newRow("noList") << Akonadi::Item::List() << 0;
    Akonadi::Item itemA;
    KContacts::Addressee addressA;
    addressA.setName(QStringLiteral("foo1"));
    itemA.setPayload<KContacts::Addressee>(addressA);
    itemA.setMimeType(KContacts::Addressee::mimeType());

    Akonadi::Item itemB;

    KContacts::Addressee addressB;
    addressB.setName(QStringLiteral("foo2"));
    itemB.setPayload<KContacts::Addressee>(addressB);
    itemB.setMimeType(KContacts::Addressee::mimeType());

    Akonadi::Item::List lst;
    lst << itemA;
    QTest::newRow("oneItem") << lst << 0;

    lst.clear();
    lst << itemA << itemA;
    QTest::newRow("oneDuplicate") << lst << 1;

    lst.clear();
    lst << itemB << itemA;
    QTest::newRow("twoDifferentItem") << lst << 0;

    lst.clear();
    lst << itemB << itemA << itemA << itemA;
    QTest::newRow("onDuplicate") << lst << 1;

    lst.clear();
    lst << itemB << itemA << itemA << itemB;
    QTest::newRow("twoDuplicate") << lst << 2;

    Akonadi::Item itemC;

    KContacts::Addressee addressC;
    addressC.setName(QStringLiteral("foo3"));
    itemC.setPayload<KContacts::Addressee>(addressC);
    itemC.setMimeType(KContacts::Addressee::mimeType());

    lst.clear();
    lst << itemB << itemC << itemA << itemA << itemB << itemC;
    QTest::newRow("threeDuplicate") << lst << 3;

    lst.clear();
    lst << itemB << itemC << itemA;
    QTest::newRow("threeDifferent") << lst << 0;
}

void SearchPotentialDuplicateContactJobTest::shouldReturnList()
{
    QFETCH(Akonadi::Item::List, listItem);
    QFETCH(int, numberOfList);

    SearchPotentialDuplicateContactJob job(listItem);
    QSignalSpy spy(&job, &SearchPotentialDuplicateContactJob::finished);
    job.start();
    QCOMPARE(spy.count(), 1);
    auto lstResult = spy.at(0).at(0).value<QVector<Akonadi::Item::List>>();
    QCOMPARE(lstResult.count(), numberOfList);
}

QTEST_MAIN(SearchPotentialDuplicateContactJobTest)
