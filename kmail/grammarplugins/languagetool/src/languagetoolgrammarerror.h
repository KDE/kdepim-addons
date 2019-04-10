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

#ifndef LANGUAGETOOLGRAMMARERROR_H
#define LANGUAGETOOLGRAMMARERROR_H

#include "grammarerror.h"
#include "liblanguagetool_private_export.h"
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolGrammarError : public GrammarError
{
public:
    LanguageToolGrammarError();
    ~LanguageToolGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;
    void setTesting(bool b);
private:
    static QStringList parseSuggestion(const QJsonObject &obj);
    bool mTesting = false;
};
Q_DECLARE_METATYPE(LanguageToolGrammarError)
Q_DECLARE_TYPEINFO(LanguageToolGrammarError, Q_MOVABLE_TYPE);

#endif // LANGUAGETOOLGRAMMARERROR_H
