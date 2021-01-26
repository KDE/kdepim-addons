/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTEGRAMMARERROR_H
#define GRAMMALECTEGRAMMARERROR_H

#include "grammarerror.h"
#include "libgrammalect_private_export.h"
class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteGrammarError : public GrammarError
{
public:
    GrammalecteGrammarError();
    ~GrammalecteGrammarError() override;
    void parse(const QJsonObject &obj, int blockindex) override;

private:
    static QStringList parseSuggestion(const QJsonObject &obj);
    static QColor parseColor(const QJsonObject &obj);
};
Q_DECLARE_METATYPE(GrammalecteGrammarError)
Q_DECLARE_TYPEINFO(GrammalecteGrammarError, Q_MOVABLE_TYPE);

#endif // GRAMMALECTEGRAMMARERROR_H
