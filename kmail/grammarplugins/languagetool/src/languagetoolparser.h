/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLPARSER_H
#define LANGUAGETOOLPARSER_H

#include "liblanguagetool_private_export.h"

#include <grammarerror.h>

class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolParser
{
public:
    LanguageToolParser();
    ~LanguageToolParser();
    QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};

#endif // LANGUAGETOOLPARSER_H
