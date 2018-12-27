/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "adblockblockableitemsjobtest.h"
#include "../adblockblockableitemsjob.h"
#include <QTest>
#include <QSignalSpy>

Q_DECLARE_METATYPE(QVector<AdBlock::AdBlockResult>)

AdBlockBlockableItemsJobTest::AdBlockBlockableItemsJobTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QVector<AdBlock::AdBlockResult> >();
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
    QSignalSpy blockableItemsSpy(&job, SIGNAL(searchItemsDone(QVector<AdBlock::AdBlockResult>)));
    job.start();
    QCOMPARE(blockableItemsSpy.count(), 1);
    const QVector<AdBlock::AdBlockResult> resultLst = blockableItemsSpy.at(0).at(0).value<QVector<AdBlock::AdBlockResult> >();
    QCOMPARE(resultLst.count(), 0);
}

void AdBlockBlockableItemsJobTest::shouldReturnAddBlockItem()
{
    //TODO
}

QTEST_MAIN(AdBlockBlockableItemsJobTest)
