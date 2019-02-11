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

int GrammarError::end() const
{
    return mEnd;
}

void GrammarError::setEnd(int end)
{
    mEnd = end;
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
    if ((mEnd != -1) && (mStart != -1) && (!mError.isEmpty())) {
        return true;
    }
    return false;
}

//Make as virtual
void GrammarError::parse(const QJsonObject &obj, int blockindex)
{
    mEnd = obj[QStringLiteral("nEnd")].toInt(-1);
    mStart = obj[QStringLiteral("nStart")].toInt(-1);
    mError = obj[QStringLiteral("sMessage")].toString();
    if (mEnd != -1) {
        mBlockId = blockindex;
        mColor = parseColor(obj);
        mSuggestions = parseSuggestion(obj);
    }
    mRule = obj[QStringLiteral("sRuleId")].toString();
    mOption = obj[QStringLiteral("sType")].toString();
    mUrl = obj[QStringLiteral("URL")].toString();
}

bool GrammarError::operator ==(const GrammarError &other) const
{
    return (mBlockId == other.blockId())
           && (mEnd == other.end())
           && (mStart == other.start())
           && (mColor == other.color())
           && (mSuggestions == other.suggestions())
           && (mError == other.error())
           && (mOption == other.option())
           && (mRule == other.rule())
           && (mUrl == other.url());
}

QStringList GrammarError::parseSuggestion(const QJsonObject &obj)
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

QColor GrammarError::parseColor(const QJsonObject &obj)
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
        qCWarning(LIBGRAMMARCOMMON_LOG) << "Parsing color: Array is not correct:" << array;
    }
    return col;
}

QDebug operator <<(QDebug d, const GrammarError &t)
{
    d << "mError: " << t.error();
    d << "Start: " << t.start();
    d << "End: " << t.end();
    d << "BlockId: " << t.blockId();
    d << "Color: " << t.color().name();
    d << "Suggestion: " << t.suggestions();
    d << "Option: " << t.option();
    d << "Rule: " << t.rule();
    d << "Url: " << t.url();
    return d;
}
