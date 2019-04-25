/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "markdownutiltest.h"
#include "markdownutil.h"
#include <QTest>
QTEST_GUILESS_MAIN(MarkdownUtilTest)

MarkdownUtilTest::MarkdownUtilTest(QObject *parent)
    : QObject(parent)
{

}

void MarkdownUtilTest::shouldConvert()
{
    QFETCH(QString, input);
    QFETCH(QStringList, results);
    QCOMPARE(MarkdownUtil::imagePaths(input), results);
}

void MarkdownUtilTest::shouldConvert_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QStringList>("results");
    QTest::newRow("empty") <<  QString() << QStringList();
    QTest::newRow("any") <<  QStringLiteral("![foo]") << QStringList();
    QTest::newRow("any-2") <<  QStringLiteral("![foo]() qsdqsdq") << (QStringList() << QString());
    QStringList result;
    result << QStringLiteral("image.png");
    QTest::newRow("one item") <<  QStringLiteral("![foo](image.png \"ss\") bla") << result;
    result.clear();
    result << QStringLiteral("image.png");
    result << QStringLiteral("image2.png");
    QTest::newRow("two item") <<  QStringLiteral("![foo](image.png \"ss\") bla ![bli](image2.png \"sdsd\")") << result;
    QTest::newRow("two item-2") <<  QStringLiteral("![foo](image.png) bla ![bli](image2.png)") << result;
    QTest::newRow("two item-3") <<  QStringLiteral("![foo](image.png  \"blz\") bla ![bli](image2.png)") << result;
    QTest::newRow("two item-3") <<  QStringLiteral("![foo](image.png  \"blz\") bla ![bli](image2.png \"ez\" )") << result;
}
