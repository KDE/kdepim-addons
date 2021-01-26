/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLLISTOFLANGUAGESPARSER_H
#define LANGUAGETOOLLISTOFLANGUAGESPARSER_H

#include "languageinfo.h"
#include "liblanguagetool_private_export.h"
#include <QVector>
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolListOfLanguagesParser
{
public:
    LanguageToolListOfLanguagesParser();
    ~LanguageToolListOfLanguagesParser();
    QVector<LanguageInfo> parseResult(const QJsonArray &obj) const;
};

#endif // LANGUAGETOOLLISTOFLANGUAGESPARSER_H
