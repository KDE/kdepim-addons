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

#include "grammalectegrammarerror.h"
#include "grammalecteplugin_debug.h"

#include <QJsonArray>
#include <QJsonObject>

GrammalecteGrammarError::GrammalecteGrammarError()
{

}

GrammalecteGrammarError::~GrammalecteGrammarError()
{

}

QColor GrammalecteGrammarError::color() const
{
    return mColor;
}

void GrammalecteGrammarError::setColor(const QColor &color)
{
    mColor = color;
}

QString GrammalecteGrammarError::error() const
{
    return mError;
}

void GrammalecteGrammarError::setError(const QString &error)
{
    mError = error;
}

int GrammalecteGrammarError::blockId() const
{
    return mBlockId;
}

void GrammalecteGrammarError::setBlockId(int blockId)
{
    mBlockId = blockId;
}

int GrammalecteGrammarError::begin() const
{
    return mBegin;
}

void GrammalecteGrammarError::setBegin(int begin)
{
    mBegin = begin;
}

int GrammalecteGrammarError::end() const
{
    return mEnd;
}

void GrammalecteGrammarError::setEnd(int end)
{
    mEnd = end;
}

QStringList GrammalecteGrammarError::suggestions() const
{
    return mSuggestions;
}

void GrammalecteGrammarError::setSuggestions(const QStringList &suggestions)
{
    mSuggestions = suggestions;
}

bool GrammalecteGrammarError::isValid() const
{
    //TODO
    if ((mEnd != -1) && (mBegin != -1))
        return true;
    return false;
}

void GrammalecteGrammarError::parse(const QJsonObject &obj, int blockindex)
{
    mBlockId = blockindex;
    mEnd = obj[QStringLiteral("nEnd")].toInt();
    mBegin = obj[QStringLiteral("nStart")].toInt();
    mError = obj[QStringLiteral("sMessage")].toString();
    mColor = parseColor(obj);
    mSuggestions = parseSuggestion(obj);
    //TODO
}

QStringList GrammalecteGrammarError::parseSuggestion(const QJsonObject &obj)
{
    QStringList lst;
    const QJsonArray array = obj[QStringLiteral("aSuggestions")].toArray();
    const QVariantList list = array.toVariantList();
    for (const QVariant &v : list) {
        qDebug() << " v" << v.toString();
        lst.append(v.toString());
    }
    return lst;
}

QColor GrammalecteGrammarError::parseColor(const QJsonObject &obj)
{
    QColor col;
    const QJsonArray array = obj[QStringLiteral("aColor")].toArray();
    if (array.count() == 3) {
        const QVariantList list = array.toVariantList();
//        for (const QVariant &v : list) {
//            qDebug() << " v" << v.toInt();
//        }
        col = QColor(array.at(0).toInt(), array.at(1).toInt(), array.at(2).toInt());
    } else {
        qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Parsing color: Array is not correct:" << array;
    }
    return col;
}

QDebug operator <<(QDebug d, const GrammalecteGrammarError &t)
{
    d << "mError: " << t.error();
    d << "Start: " << t.begin();
    d << "End: " << t.end();
    d << "BlockId: " << t.blockId();
    d << "Color: " << t.color().name();
    d << "Suggestion: " << t.suggestions();
    return d;
}
