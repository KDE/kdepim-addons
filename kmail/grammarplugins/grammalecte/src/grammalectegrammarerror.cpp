/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#include "grammalectegrammarerror.h"
#include "libgrammalecte_debug.h"

#include <QJsonArray>

GrammalecteGrammarError::GrammalecteGrammarError()
{
}

GrammalecteGrammarError::~GrammalecteGrammarError()
{
}

QStringList GrammalecteGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QStringLiteral("aSuggestions")].toArray();
    const QVariantList list = array.toVariantList();
    for (const QVariant &v : list) {
        //qDebug() << " v" << v.toString();
        lst.append(v.toString());
    }
    return lst;
}

QColor GrammalecteGrammarError::parseColor(const QJsonObject &obj)
{
    QColor col;
    const QJsonArray array = obj[QStringLiteral("aColor")].toArray();
    if (array.isEmpty()) {
        return col;
    }
    if (array.count() == 3) {
        const QVariantList list = array.toVariantList();
//        for (const QVariant &v : list) {
//            qDebug() << " v" << v.toInt();
//        }
        col = QColor(array.at(0).toInt(), array.at(1).toInt(), array.at(2).toInt());
    } else {
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Parsing color: Array is not correct:" << array;
    }
    return col;
}

void GrammalecteGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    const int end = obj[QStringLiteral("nEnd")].toInt(-1);
    mStart = obj[QStringLiteral("nStart")].toInt(-1);
    if (end != -1) {
        mLength = end - mStart;
    }
    mError = obj[QStringLiteral("sMessage")].toString();
    if (mLength != -1) {
        mBlockId = blockindex;
        mColor = parseColor(obj);
        mSuggestions = parseSuggestion(obj);
    }
    mRule = obj[QStringLiteral("sRuleId")].toString();
    mOption = obj[QStringLiteral("sType")].toString();
    mUrl = obj[QStringLiteral("URL")].toString();
}
