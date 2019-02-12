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

#include "languagetoolgrammarerror.h"

#include <QJsonArray>

LanguagetoolGrammarError::LanguagetoolGrammarError()
{

}

LanguagetoolGrammarError::~LanguagetoolGrammarError()
{

}

void LanguagetoolGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    mError = obj[QStringLiteral("message")].toString();
    mStart = obj[QStringLiteral("offset")].toInt(-1);
    mLength = obj[QStringLiteral("length")].toInt(-1);
    mSuggestions = parseSuggestion(obj);
    //TODO ???
//    mRule = obj[QStringLiteral("sRuleId")].toString();
//    mOption = obj[QStringLiteral("sType")].toString();
//    mUrl = obj[QStringLiteral("URL")].toString();
}


QStringList LanguagetoolGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QStringLiteral("replacements")].toArray();
    const QVariantList list = array.toVariantList();
    for (const QVariant &v : list) {
        //qDebug() << " v" << v.toString();
        lst.append(v.toString());
    }
    return lst;
}
