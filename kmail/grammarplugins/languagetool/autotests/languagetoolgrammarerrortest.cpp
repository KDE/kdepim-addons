/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerrortest.h"
#include "languagetoolgrammarerror.h"
#include <QJsonDocument>
#include <QTest>
QTEST_GUILESS_MAIN(LanguageToolGrammarErrorTest)
LanguageToolGrammarErrorTest::LanguageToolGrammarErrorTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolGrammarErrorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("nbBlock");
    QTest::addColumn<LanguageToolGrammarError>("error");
    LanguageToolGrammarError err;
    err.setBlockId(2);
    err.setStart(3);
    err.setLength(8);
    err.setColor(QColor(Qt::red));
    err.setSuggestions(QStringList() << QStringLiteral("ne suis pas"));
    err.setError(QStringLiteral("Voulez-vous écrire \"ne suis pas\" ?"));
    //err.setOption(QStringLiteral("maj"));
    err.setRule(QStringLiteral("P_V_PAS"));
    err.setUrl(QStringLiteral("http://www.academie-francaise.fr/ne"));
    QTest::newRow("parse-error1") << QStringLiteral("parse-error1") << 1 << err;
}

void LanguageToolGrammarErrorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, nbBlock);
    QFETCH(LanguageToolGrammarError, error);
    const QString originalJsonFile = QLatin1String(LANGUAGETOOL_DATA_DIR) + QLatin1Char('/') + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    LanguageToolGrammarError parser;
    parser.setTesting(true);
    parser.parse(fields, nbBlock);
    const bool compare = (parser == error);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " error " << error;
    }
    QVERIFY(compare);
}
