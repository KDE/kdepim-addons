/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteGrammarErrorTest)

GrammalecteGrammarErrorTest::GrammalecteGrammarErrorTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteGrammarErrorTest::shouldHaveDefaultValue()
{
    GrammalecteGrammarError info;
    QCOMPARE(info.length(), -1);
    QCOMPARE(info.start(), -1);
    QCOMPARE(info.blockId(), -1);
    QVERIFY(info.error().isEmpty());
    QVERIFY(info.suggestions().isEmpty());
    QVERIFY(!info.color().isValid());
    QVERIFY(!info.isValid());
}

void GrammalecteGrammarErrorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("nbBlock");
    QTest::addColumn<GrammalecteGrammarError>("error");
    QTest::newRow("empty-error") << QStringLiteral("empty-error") << 1 << GrammalecteGrammarError();
    GrammalecteGrammarError err;
    err.setBlockId(1);
    err.setStart(15);
    err.setLength(5);
    err.setColor(QColor(217, 128, 38));
    err.setSuggestions(QStringList() << QStringLiteral("Alors"));
    err.setError(QStringLiteral("Après un point, une majuscule est généralement requise."));
    err.setOption(QStringLiteral("maj"));
    err.setRule(QStringLiteral("majuscule_après_point"));
    QTest::newRow("error1") << QStringLiteral("error1") << 1 << err;
    err.setColor(QColor());
    QTest::newRow("empty-color") << QStringLiteral("empty-color") << 1 << err;
}

void GrammalecteGrammarErrorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, nbBlock);
    QFETCH(GrammalecteGrammarError, error);
    const QString originalJsonFile = QLatin1String(GRAMMALECTE_DATA_DIR) + QLatin1Char('/') + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    GrammalecteGrammarError parser;
    parser.parse(fields, nbBlock);
    const bool compare = (parser == error);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " error " << error;
    }
    QVERIFY(compare);
}
