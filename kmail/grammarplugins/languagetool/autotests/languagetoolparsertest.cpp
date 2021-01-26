/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolparsertest.h"
#include "languagetoolparser.h"
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(LanguageToolParserTest)
LanguageToolParserTest::LanguageToolParserTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolParserTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfElement");
    QTest::newRow("noerror") << QStringLiteral("noerror") << 0;
    QTest::newRow("test1") << QStringLiteral("test1") << 1;
    QTest::newRow("test2") << QStringLiteral("test2") << 3;
}

void LanguageToolParserTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfElement);
    const QString originalJsonFile = QLatin1String(LANGUAGETOOL_DATA_DIR) + QLatin1Char('/') + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    LanguageToolParser parser;
    QCOMPARE(parser.parseResult(fields).count(), numberOfElement);
}
