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
    // err.setRule(QStringLiteral("majuscule_après_point"));
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
    parser.parse(fields, nbBlock);
    const bool compare = (parser == error);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " error " << error;
    }
    QVERIFY(compare);
}
