/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "confirmbeforedeletingrule.h"
#include "kmailconfirmbeforedeleting_export.h"
#include <QObject>
#include <QVector>

class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingManager(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingManager() override;

    static ConfirmBeforeDeletingManager *self();

private:
    QVector<ConfirmBeforeDeletingRule> mRules;
};
