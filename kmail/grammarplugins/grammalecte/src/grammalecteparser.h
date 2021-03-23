/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammalectegrammarerror.h"
#include "libgrammalect_private_export.h"
#include <QJsonObject>
#include <QVector>
class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteParser
{
public:
    GrammalecteParser();
    ~GrammalecteParser();
    Q_REQUIRED_RESULT QVector<GrammarError> parseResult(const QJsonObject &obj) const;
};

