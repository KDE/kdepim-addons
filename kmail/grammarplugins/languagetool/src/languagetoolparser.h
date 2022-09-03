/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "liblanguagetool_private_export.h"

#include <grammarerror.h>

class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolParser
{
public:
    LanguageToolParser();
    ~LanguageToolParser();
    Q_REQUIRED_RESULT QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};
