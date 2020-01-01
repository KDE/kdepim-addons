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

#ifndef LANGUAGEINFO_H
#define LANGUAGEINFO_H
#include "liblanguagetool_private_export.h"

#include <QObject>
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageInfo
{
public:
    LanguageInfo();
    ~LanguageInfo();

    Q_REQUIRED_RESULT QString name() const;
    void setName(const QString &name);

    Q_REQUIRED_RESULT QString longCode() const;
    void setLongCode(const QString &longCode);

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code);

    Q_REQUIRED_RESULT bool isValid() const;

    void parse(const QJsonObject &obj);

private:
    QString mName;
    QString mLongCode;
    QString mCode;
};
Q_DECLARE_METATYPE(LanguageInfo)
Q_DECLARE_TYPEINFO(LanguageInfo, Q_MOVABLE_TYPE);

#endif // LANGUAGEINFO_H
