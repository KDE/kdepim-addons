/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresultutiltest.h"
#include "grammarresultutil.h"
#include <QTest>
#include <QTextDocument>
QTEST_MAIN(GrammarResultUtilTest)
GrammarResultUtilTest::GrammarResultUtilTest(QObject *parent)
    : QObject{parent}
{
}

void GrammarResultUtilTest::shouldReplaceWord()
{
    typedef QVector<MessageComposer::PluginGrammarAction> ListGrammarActions;
    typedef QVector<GrammarError> ErrorInfosList;
    QFETCH(QString, initialText);
    QFETCH(QString, replacementWord);
    QFETCH(ErrorInfosList, grammarErrors);
    QFETCH(ListGrammarActions, listGrammarActions);
    QFETCH(QString, resultText);

    QTextDocument doc;
    doc.setPlainText(initialText);
    GrammarResultUtil::applyGrammarResult(grammarErrors, &doc, Qt::red);
    for (const auto &action : listGrammarActions) {
        GrammarResultUtil::replaceWord(action, replacementWord, &doc);
    }
    QCOMPARE(doc.toPlainText(), resultText);
}

void GrammarResultUtilTest::shouldReplaceWord_data()
{
    QTest::addColumn<QString>("initialText");
    QTest::addColumn<QString>("replacementWord");
    QTest::addColumn<QVector<GrammarError>>("grammarErrors");
    QTest::addColumn<QVector<MessageComposer::PluginGrammarAction>>("listGrammarActions");
    QTest::addColumn<QString>("resultText");
    {
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        QVector<GrammarError> grammarErrorLists;
        QTest::newRow("noerror") << QString() << QString() << grammarErrorLists << lstGrammarActions << QString();
    }
}
