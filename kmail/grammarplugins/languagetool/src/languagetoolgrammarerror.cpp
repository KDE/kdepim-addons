/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerror.h"
#include "liblanguagetool_debug.h"
#include "languagetoolmanager.h"

#include <QJsonArray>

LanguageToolGrammarError::LanguageToolGrammarError()
{
}

LanguageToolGrammarError::~LanguageToolGrammarError()
{
}

void LanguageToolGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    //We use block id index based on 1 in API
    mBlockId = blockindex + 1;
    mError = obj[QStringLiteral("message")].toString();
    mStart = obj[QStringLiteral("offset")].toInt(-1);
    mLength = obj[QStringLiteral("length")].toInt(-1);
    mSuggestions = parseSuggestion(obj);
    const QJsonObject rulesObj = obj[QStringLiteral("rule")].toObject();
    if (!rulesObj.isEmpty()) {
        mRule = rulesObj[QStringLiteral("id")].toString();
        const QJsonArray urlArray = rulesObj[QStringLiteral("urls")].toArray();
        if (!urlArray.isEmpty()) {
            if (urlArray.count() > 1) {
                qCWarning(LIBLANGUAGE_PLUGIN_LOG) << "LanguageToolGrammarError::parse : more than 1 url found. Perhaps need to adapt api ";
            }
            mUrl = urlArray.at(0)[QLatin1String("value")].toString();
            //qDebug() << " mUrl" << mUrl;
        }
    }
    if (!mRule.isEmpty() && !mTesting) {
        mColor = LanguageToolManager::self()->grammarColorForError(mRule);
    } else {
        mColor = QColor(Qt::red);
    }
}

void LanguageToolGrammarError::setTesting(bool b)
{
    mTesting = b;
}

QStringList LanguageToolGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QStringLiteral("replacements")].toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            const QJsonObject suggestionObject = current.toObject();
            lst.append(suggestionObject[QLatin1String("value")].toString());
        }
    }
    //qDebug() << " lst : " << lst;
    return lst;
}
