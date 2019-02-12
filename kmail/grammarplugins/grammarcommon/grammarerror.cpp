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

#include "grammarerror.h"
#include "grammarcommon_debug.h"

#include <QJsonArray>
#include <QJsonObject>

GrammarError::GrammarError()
{
}

GrammarError::~GrammarError()
{
}

QColor GrammarError::color() const
{
    return mColor;
}

void GrammarError::setColor(const QColor &color)
{
    mColor = color;
}

QString GrammarError::error() const
{
    return mError;
}

void GrammarError::setError(const QString &error)
{
    mError = error;
}

int GrammarError::blockId() const
{
    return mBlockId;
}

void GrammarError::setBlockId(int blockId)
{
    mBlockId = blockId;
}

int GrammarError::start() const
{
    return mStart;
}

void GrammarError::setStart(int begin)
{
    mStart = begin;
}

int GrammarError::length() const
{
    return mLength;
}

void GrammarError::setLength(int length)
{
    mLength = length;
}

QStringList GrammarError::suggestions() const
{
    return mSuggestions;
}

void GrammarError::setSuggestions(const QStringList &suggestions)
{
    mSuggestions = suggestions;
}

bool GrammarError::isValid() const
{
    if ((mLength != -1) && (mStart != -1) && (!mError.isEmpty())) {
        return true;
    }
    return false;
}

void GrammarError::parse(const QJsonObject &obj, int blockindex)
{
    Q_UNUSED(obj);
    Q_UNUSED(blockindex);
}

bool GrammarError::operator ==(const GrammarError &other) const
{
    return (mBlockId == other.blockId())
           && (mLength == other.length())
           && (mStart == other.start())
           && (mColor == other.color())
           && (mSuggestions == other.suggestions())
           && (mError == other.error())
           && (mOption == other.option())
           && (mRule == other.rule())
           && (mUrl == other.url());
}


QString GrammarError::url() const
{
    return mUrl;
}

void GrammarError::setUrl(const QString &url)
{
    mUrl = url;
}

QString GrammarError::rule() const
{
    return mRule;
}

void GrammarError::setRule(const QString &rule)
{
    mRule = rule;
}

QString GrammarError::option() const
{
    return mOption;
}

void GrammarError::setOption(const QString &option)
{
    mOption = option;
}

QDebug operator <<(QDebug d, const GrammarError &t)
{
    d << "mError: " << t.error();
    d << "Start: " << t.start();
    d << "Length: " << t.length();
    d << "BlockId: " << t.blockId();
    d << "Color: " << t.color().name();
    d << "Suggestion: " << t.suggestions();
    d << "Option: " << t.option();
    d << "Rule: " << t.rule();
    d << "Url: " << t.url();
    return d;
}
