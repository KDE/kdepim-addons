/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTEPARSER_H
#define GRAMMALECTEPARSER_H

#include <QVector>
#include <QJsonObject>
#include "libgrammalect_private_export.h"
#include "grammalectegrammarerror.h"
class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteParser
{
public:
    GrammalecteParser();
    ~GrammalecteParser();
    Q_REQUIRED_RESULT QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};

#endif // GRAMMALECTEPARSER_H
