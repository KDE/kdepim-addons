/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "adblockresulttest.h"
#include "../adblockblockableitemsjob.h"
#include <QTest>

AdBlockResultTest::AdBlockResultTest(QObject *parent)
    : QObject(parent)
{

}

AdBlockResultTest::~AdBlockResultTest()
{

}

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
