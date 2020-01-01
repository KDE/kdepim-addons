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

#include "languagetoollistoflanguagesparser.h"

#include <QJsonArray>
#include <QJsonObject>

LanguageToolListOfLanguagesParser::LanguageToolListOfLanguagesParser()
{
}

LanguageToolListOfLanguagesParser::~LanguageToolListOfLanguagesParser()
{
}

QVector<LanguageInfo> LanguageToolListOfLanguagesParser::parseResult(const QJsonArray &array) const
{
    QVector<LanguageInfo> lstLanguageInfo;
    for (const QJsonValue &current : array) {
        //qDebug() << " current " << current;
        if (current.type() == QJsonValue::Object) {
            const QJsonObject languageToolObject = current.toObject();
            LanguageInfo lang;
            lang.parse(languageToolObject);
            if (lang.isValid()) {
                lstLanguageInfo.append(lang);
            }
        }
    }
    return lstLanguageInfo;
}
