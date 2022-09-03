/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammarerror.h"
#include "liblanguagetool_private_export.h"
#include <QStringList>

class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolGrammarError : public GrammarError
{
public:
    LanguageToolGrammarError();
    ~LanguageToolGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;
    void setTesting(bool b);

private:
    Q_REQUIRED_RESULT static QStringList parseSuggestion(const QJsonObject &obj);
    bool mTesting = false;
};
Q_DECLARE_METATYPE(LanguageToolGrammarError)
Q_DECLARE_TYPEINFO(LanguageToolGrammarError, Q_MOVABLE_TYPE);
