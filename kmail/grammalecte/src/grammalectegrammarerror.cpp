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

void GrammalecteGrammarError::parse(const QJsonObject &obj)
{
    //mBlockId = obj[QLatin1String("iParagraph")].toInt();
    //TODO
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
