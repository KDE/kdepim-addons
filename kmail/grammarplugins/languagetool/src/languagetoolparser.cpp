/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerror.h"
#include "languagetoolparser.h"
#include "liblanguagetool_debug.h"

#include <QJsonArray>

LanguageToolParser::LanguageToolParser()
{
}

LanguageToolParser::~LanguageToolParser()
{
}

QVector<GrammarError> LanguageToolParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammarError> infos;
    const QJsonArray array = obj.value(QLatin1String("matches")).toArray();
    for (const QJsonValue &current : array) {
        //qDebug() << " current " << current;
        if (current.type() == QJsonValue::Object) {
            const QJsonObject languageToolObject = current.toObject();
            LanguageToolGrammarError error;
            error.parse(languageToolObject, 0);
            if (error.isValid()) {
                infos.append(error);
            }
        }
    }
    return infos;
}
