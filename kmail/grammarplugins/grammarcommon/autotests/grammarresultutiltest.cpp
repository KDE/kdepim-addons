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
    QFETCH(QStringList, replacementWord);
    QFETCH(ErrorInfosList, grammarErrors);
    QFETCH(ListGrammarActions, listGrammarActions);
    QFETCH(QString, resultText);

    QTextDocument doc;
    doc.setPlainText(initialText);
    GrammarResultUtil::applyGrammarResult(grammarErrors, &doc, Qt::red);
    int i = 0;
    for (const auto &action : listGrammarActions) {
        GrammarResultUtil::replaceWord(action, replacementWord.at(i), &doc);
        ++i;
    }
    QCOMPARE(doc.toPlainText(), resultText);
}

void GrammarResultUtilTest::shouldReplaceWord_data()
{
    QTest::addColumn<QString>("initialText");
    QTest::addColumn<QStringList>("replacementWord");
    QTest::addColumn<QVector<GrammarError>>("grammarErrors");
    QTest::addColumn<QVector<MessageComposer::PluginGrammarAction>>("listGrammarActions");
    QTest::addColumn<QString>("resultText");
    {
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        QVector<GrammarError> grammarErrorLists;
        QTest::newRow("noerror") << QString() << QStringList() << grammarErrorLists << lstGrammarActions << QString();
    }
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        QVector<GrammarError> grammarErrorLists;
        QTest::newRow("noerror2") << text << QStringList() << grammarErrorLists << lstGrammarActions << text;
    }
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral("joo")};
        const QString result = QStringLiteral("joo foo, ah car");
        QTest::newRow("error1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = QStringList{QStringLiteral("ppppppp")};
        const QString result = QStringLiteral("ppppppp foo, ah car");
        QTest::newRow("error2-word-big") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = QStringList{QStringLiteral("p")};
        const QString result = QStringLiteral("p foo, ah car");
        QTest::newRow("error3-word-smaller") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    // Two errors
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(4);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(4);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral("joo"), QStringLiteral("AAA")};
        const QString result = QStringLiteral("joo AAA, ah car");
        QTest::newRow("error1-with-two-errors") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    // Bug 459113
    {
        const QString text = QStringLiteral("Boo foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(4);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(6);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral("jooAA"), QStringLiteral("AAA")};
        const QString result = QStringLiteral("jooAA AAA, ah car");
        QTest::newRow("error1-with-two-errors-bigger") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
    {
        const QString text = QStringLiteral("Boo\n foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(5);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(2);
            act.setStart(1);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral("jooAA"), QStringLiteral("AAA")};
        const QString result = QStringLiteral("jooAA\n AAA, ah car");
        QTest::newRow("error1-with-two-errors-bigger-1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    {
        const QString text = QStringLiteral("Boo\n foo, ah car");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(0);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(5);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(0);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(2);
            act.setStart(1);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral("b"), QStringLiteral("AAA")};
        const QString result = QStringLiteral("b\n AAA, ah car");
        QTest::newRow("error1-with-two-errors-smaller-1") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }

    {
        const QString text = QStringLiteral("Je suis  la qui empeche\nil est la.\n tout passage dans l'herbe");
        QVector<GrammarError> grammarErrorLists;
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(7);
            err.setLength(2);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(1);
            err.setStart(14);
            err.setLength(7);
            grammarErrorLists.append(err);
        }
        {
            GrammarError err;
            err.setBlockId(2);
            err.setStart(3);
            err.setLength(3);
            grammarErrorLists.append(err);
        }
        QVector<MessageComposer::PluginGrammarAction> lstGrammarActions;
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(7);
            act.setLength(2);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(1);
            act.setStart(15);
            act.setLength(7);
            lstGrammarActions.append(act);
        }
        {
            MessageComposer::PluginGrammarAction act;
            act.setBlockId(2);
            act.setStart(3);
            act.setLength(3);
            lstGrammarActions.append(act);
        }
        const QStringList replacement = {QStringLiteral(" "), QStringLiteral("EMPECHE"), QStringLiteral("A")};
        const QString result = QStringLiteral("Je suis la qui EMPECHE\nil A la.\n tout passage dans l'herbe");
        QTest::newRow("error3") << text << replacement << grammarErrorLists << lstGrammarActions << result;
    }
}
