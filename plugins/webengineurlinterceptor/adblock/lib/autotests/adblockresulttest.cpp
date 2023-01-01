/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockresulttest.h"
#include "../adblockblockableitemsjob.h"
#include <QTest>

AdBlockResultTest::AdBlockResultTest(QObject *parent)
    : QObject(parent)
{
}

AdBlockResultTest::~AdBlockResultTest() = default;

void AdBlockResultTest::shouldHaveDefaultValue()
{
    AdBlock::AdBlockResult result;
    QVERIFY(result.src.isEmpty());
    QCOMPARE(result.type, AdBlock::AdBlockBlockableItemsJob::UnKnown);
    QVERIFY(!result.isValid());
}

void AdBlockResultTest::shouldBeValid()
{
    AdBlock::AdBlockResult result;
    const QString src = QStringLiteral("source");
    const AdBlock::AdBlockBlockableItemsJob::TypeElement element = AdBlock::AdBlockBlockableItemsJob::Image;
    result.src = src;
    result.type = element;
    QVERIFY(result.isValid());

    result.src.clear();
    QVERIFY(!result.isValid());
    result.src = src;
    result.type = AdBlock::AdBlockBlockableItemsJob::UnKnown;
    QVERIFY(!result.isValid());
}

QTEST_APPLESS_MAIN(AdBlockResultTest)
