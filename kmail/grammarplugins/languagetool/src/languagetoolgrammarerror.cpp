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

LanguagetoolGrammarError::LanguagetoolGrammarError()
{

}

LanguagetoolGrammarError::~LanguagetoolGrammarError()
{

}

void LanguagetoolGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    mError = obj[QStringLiteral("message")].toString();

//    mEnd = obj[QStringLiteral("nEnd")].toInt(-1);
//    mStart = obj[QStringLiteral("nStart")].toInt(-1);
//    if (mEnd != -1) {
//        mBlockId = blockindex;
//        //mColor = parseColor(obj);
//        //mSuggestions = parseSuggestion(obj);
//    }
//    mRule = obj[QStringLiteral("sRuleId")].toString();
//    mOption = obj[QStringLiteral("sType")].toString();
//    mUrl = obj[QStringLiteral("URL")].toString();
}


QStringList LanguagetoolGrammarError::parseSuggestion(const QJsonObject &obj)
{
    //TODO
    return {};
}
