/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemsjobtest.h"
#include "../adblockblockableitemsjob.h"
#include <QSignalSpy>
#include <QTest>

Q_DECLARE_METATYPE(QVector<AdBlock::AdBlockResult>)

AdBlockBlockableItemsJobTest::AdBlockBlockableItemsJobTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QVector<AdBlock::AdBlockResult>>();
}

AdBlockBlockableItemsJobTest::~AdBlockBlockableItemsJobTest()
{
}

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
    const QVector<AdBlock::AdBlockResult> resultLst = blockableItemsSpy.at(0).at(0).value<QVector<AdBlock::AdBlockResult>>();
    QCOMPARE(resultLst.count(), 0);
}

void AdBlockBlockableItemsJobTest::shouldReturnAddBlockItem()
{
    // TODO
}

QTEST_MAIN(AdBlockBlockableItemsJobTest)
