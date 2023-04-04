/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemsjobtest.h"
#include "../adblockblockableitemsjob.h"
#include <QSignalSpy>
#include <QTest>

Q_DECLARE_METATYPE(QList<AdBlock::AdBlockResult>)

AdBlockBlockableItemsJobTest::AdBlockBlockableItemsJobTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QList<AdBlock::AdBlockResult>>();
}

AdBlockBlockableItemsJobTest::~AdBlockBlockableItemsJobTest() = default;

void AdBlockBlockableItemsJobTest::shouldHaveDefaultValue()
{
    AdBlock::AdBlockBlockableItemsJob job;
    QVERIFY(!job.webEngineView());
}

void AdBlockBlockableItemsJobTest::shouldReturnEmptyListWhenWebEngineIsNotSet()
{
    AdBlock::AdBlockBlockableItemsJob job;
    QSignalSpy blockableItemsSpy(&job, &AdBlock::AdBlockBlockableItemsJob::searchItemsDone);
    job.start();
    QCOMPARE(blockableItemsSpy.count(), 1);
    const auto resultLst = blockableItemsSpy.at(0).at(0).value<QList<AdBlock::AdBlockResult>>();
    QCOMPARE(resultLst.count(), 0);
}

void AdBlockBlockableItemsJobTest::shouldReturnAddBlockItem()
{
    // TODO
}

QTEST_MAIN(AdBlockBlockableItemsJobTest)
