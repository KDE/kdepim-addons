/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
