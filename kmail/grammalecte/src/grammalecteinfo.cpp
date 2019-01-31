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

#include "grammalecteinfo.h"

GrammalecteInfo::GrammalecteInfo()
{

}

GrammalecteInfo::~GrammalecteInfo()
{

}

QColor GrammalecteInfo::color() const
{
    return mColor;
}

void GrammalecteInfo::setColor(const QColor &color)
{
    mColor = color;
}

QString GrammalecteInfo::error() const
{
    return mError;
}

void GrammalecteInfo::setError(const QString &error)
{
    mError = error;
}

int GrammalecteInfo::blockId() const
{
    return mBlockId;
}

void GrammalecteInfo::setBlockId(int blockId)
{
    mBlockId = blockId;
}

int GrammalecteInfo::begin() const
{
    return mBegin;
}

void GrammalecteInfo::setBegin(int begin)
{
    mBegin = begin;
}

int GrammalecteInfo::end() const
{
    return mEnd;
}

void GrammalecteInfo::setEnd(int end)
{
    mEnd = end;
}

QStringList GrammalecteInfo::suggestions() const
{
    return mSuggestions;
}

void GrammalecteInfo::setSuggestions(const QStringList &suggestions)
{
    mSuggestions = suggestions;
}

bool GrammalecteInfo::isValid() const
{
    //TODO
    return false;
}
