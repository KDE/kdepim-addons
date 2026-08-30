/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownutiltest.h"
#include "markdownutil.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
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
    QTest::newRow("any") << u"![foo]"_s << QStringList();
    QTest::newRow("any-2") << u"![foo]() qsdqsdq"_s << (QStringList() << QString());
    QStringList result;
    result << u"image.png"_s;
    QTest::newRow("one item") << u"![foo](image.png \"ss\") bla"_s << result;
    QTest::newRow("one item-2") << u"![foo](image.png) bla"_s << result;
    result.clear();
    result << u"image.png"_s;
    result << u"image2.png"_s;
    QTest::newRow("two item") << u"![foo](image.png \"ss\") bla ![bli](image2.png \"sdsd\")"_s << result;
    QTest::newRow("two item-2") << u"![foo](image.png) bla ![bli](image2.png)"_s << result;
    QTest::newRow("two item-3") << u"![foo](image.png  \"blz\") bla ![bli](image2.png)"_s << result;
    QTest::newRow("two item-3") << u"![foo](image.png  \"blz\") bla ![bli](image2.png \"ez\" )"_s << result;

    // With size
    QTest::newRow("two item-3") << u"![foo](image.png =50x50 \"blz\") bla ![bli](image2.png \"ez\" )"_s << result;
    QTest::newRow("two item-3") << u"![foo](image.png =50x50 \"blz\") bla ![bli](image2.png =100x100 \"ez\" ) sdfsdf "_s << result;
}

#include "moc_markdownutiltest.cpp"
