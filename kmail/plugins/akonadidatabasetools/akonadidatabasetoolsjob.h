/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatabasetoolsutils.h"
#include "akonadidatasetools_private_export.h"
#include <QObject>

class AKONADIDATASETOOLS_TESTS_EXPORT AkonadiDatabaseToolsJob : public QObject
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsJob(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsJob() override;

    Q_REQUIRED_RESULT bool canStart() const;

    void start();
    void setTool(AkonadiDatabaseToolsUtils::AkonadiDatabaseTool newTool);

private:
    Q_REQUIRED_RESULT QString processExist() const;
    AkonadiDatabaseToolsUtils::AkonadiDatabaseTool mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown;
};
