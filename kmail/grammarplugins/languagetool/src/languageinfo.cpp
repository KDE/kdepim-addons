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

#include "languageinfo.h"

#include <QJsonObject>

LanguageInfo::LanguageInfo()
{
}

LanguageInfo::~LanguageInfo()
{
}

QString LanguageInfo::name() const
{
    return mName;
}

void LanguageInfo::setName(const QString &name)
{
    mName = name;
}

QString LanguageInfo::longCode() const
{
    return mLongCode;
}

void LanguageInfo::setLongCode(const QString &longCode)
{
    mLongCode = longCode;
}

QString LanguageInfo::code() const
{
    return mCode;
}

void LanguageInfo::setCode(const QString &code)
{
    mCode = code;
}

bool LanguageInfo::isValid() const
{
    //We need code and name
    return !mName.isEmpty() && !mCode.isEmpty();
}

void LanguageInfo::parse(const QJsonObject &obj)
{
    mName = obj[QStringLiteral("name")].toString();
    mCode = obj[QStringLiteral("code")].toString();
    mLongCode = obj[QStringLiteral("longCode")].toString();
}
