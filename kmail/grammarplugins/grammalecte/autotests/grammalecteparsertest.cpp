/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteparsertest.h"
#include "grammalecteparser.h"
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteParserTest)

GrammalecteParserTest::GrammalecteParserTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

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
