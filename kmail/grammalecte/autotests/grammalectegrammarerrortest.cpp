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

#include "grammalectegrammarerrortest.h"
#include "grammalectegrammarerror.h"
#include <QTest>
QTEST_MAIN(GrammalecteGrammarErrorTest)

GrammalecteGrammarErrorTest::GrammalecteGrammarErrorTest(QObject *parent)
    : QObject(parent)
{

}

void GrammalecteGrammarErrorTest::shouldHaveDefaultValue()
{
    GrammalecteGrammarError info;
    QCOMPARE(info.end(), -1);
    QCOMPARE(info.begin(), -1);
    QCOMPARE(info.blockId(), -1);
    QVERIFY(info.error().isEmpty());
    QVERIFY(info.suggestions().isEmpty());
    QVERIFY(!info.color().isValid());
    QVERIFY(!info.isValid());
}
/*
void GrammalecteParserTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfElement");
    QTest::newRow("noerror") << QStringLiteral("noerror") << 0;
    QTest::newRow("noerror2") << QStringLiteral("noerror2") << 0;
    QTest::newRow("result2") << QStringLiteral("result2") << 3;
}

void GrammalecteParserTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfElement);
    const QString originalJsonFile = QLatin1String(GRAMMALECTE_DATA_DIR) + QLatin1Char('/') + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    GrammalecteParser parser;
    QCOMPARE(parser.parseResult(fields).count(), numberOfElement);

}
*/
