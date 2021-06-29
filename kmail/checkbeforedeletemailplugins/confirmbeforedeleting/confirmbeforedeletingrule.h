/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kmailconfirmbeforedeleting_export.h"
#include <QDebug>
#include <QString>
class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingRule
{
public:
    ConfirmBeforeDeletingRule();
    ~ConfirmBeforeDeletingRule();

    Q_REQUIRED_RESULT const QString &pattern() const;
    void setPattern(const QString &newPattern);

    // TODO save/Load
private:
    QString mPattern;
};
Q_DECLARE_TYPEINFO(ConfirmBeforeDeletingRule, Q_MOVABLE_TYPE);
KMAILCONFIRMBEFOREDELETING_EXPORT QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t);
