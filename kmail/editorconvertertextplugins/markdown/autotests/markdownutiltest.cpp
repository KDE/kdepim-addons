/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    QTest::newRow("empty") << QString() << QStringList();
    QTest::newRow("any") << QStringLiteral("![foo]") << QStringList();
    QTest::newRow("any-2") << QStringLiteral("![foo]() qsdqsdq") << (QStringList() << QString());
    QStringList result;
    result << QStringLiteral("image.png");
    QTest::newRow("one item") << QStringLiteral("![foo](image.png \"ss\") bla") << result;
    QTest::newRow("one item-2") << QStringLiteral("![foo](image.png) bla") << result;
    result.clear();
    result << QStringLiteral("image.png");
    result << QStringLiteral("image2.png");
    QTest::newRow("two item") << QStringLiteral("![foo](image.png \"ss\") bla ![bli](image2.png \"sdsd\")") << result;
    QTest::newRow("two item-2") << QStringLiteral("![foo](image.png) bla ![bli](image2.png)") << result;
    QTest::newRow("two item-3") << QStringLiteral("![foo](image.png  \"blz\") bla ![bli](image2.png)") << result;
    QTest::newRow("two item-3") << QStringLiteral("![foo](image.png  \"blz\") bla ![bli](image2.png \"ez\" )") << result;

    // With size
    QTest::newRow("two item-3") << QStringLiteral("![foo](image.png =50x50 \"blz\") bla ![bli](image2.png \"ez\" )") << result;
    QTest::newRow("two item-3") << QStringLiteral("![foo](image.png =50x50 \"blz\") bla ![bli](image2.png =100x100 \"ez\" ) sdfsdf ") << result;
}

#include "moc_markdownutiltest.cpp"
