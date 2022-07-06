/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatasetools_export.h"
#include <QObject>

class AKONADIDATASETOOLS_EXPORT AkonadiDatabaseToolsJob : public QObject
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsJob(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsJob() override;

    Q_REQUIRED_RESULT bool canStart() const;

    void start();
};
