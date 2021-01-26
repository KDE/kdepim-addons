/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarerror.h"
#include "grammarcommon_debug.h"

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
    Q_UNUSED(obj)
    Q_UNUSED(blockindex)
}

bool GrammarError::operator==(const GrammarError &other) const
{
    return (mBlockId == other.blockId()) && (mLength == other.length()) && (mStart == other.start()) && (mColor == other.color())
        && (mSuggestions == other.suggestions()) && (mError == other.error()) && (mOption == other.option()) && (mRule == other.rule())
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

QDebug operator<<(QDebug d, const GrammarError &t)
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
