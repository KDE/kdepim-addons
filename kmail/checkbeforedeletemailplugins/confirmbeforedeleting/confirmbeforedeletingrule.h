/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <QString>

class ConfirmBeforeDeletingRule
{
public:
    ConfirmBeforeDeletingRule();
    ~ConfirmBeforeDeletingRule();

    Q_REQUIRED_RESULT const QString &pattern() const;
    void setPattern(const QString &newPattern);

private:
    QString mPattern;
};
