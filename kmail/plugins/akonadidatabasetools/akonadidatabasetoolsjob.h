/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatabasetoolsutils.h"
#include "akonadidatasetools_private_export.h"
#include <QObject>
class QProcess;
class AKONADIDATASETOOLS_TESTS_EXPORT AkonadiDatabaseToolsJob : public QObject
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsJob(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsJob() override;

    [[nodiscard]] bool canStart() const;

    void start();
    void setTool(AkonadiDatabaseToolsUtils::AkonadiDatabaseTool newTool);

Q_SIGNALS:
    void receivedStandardError(const QString &str);
    void receivedStandardOutput(const QString &str);
    void finished();

private:
    [[nodiscard]] AKONADIDATASETOOLS_NO_EXPORT QString akonadiProcessPath() const;
    AkonadiDatabaseToolsUtils::AkonadiDatabaseTool mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown;
    QProcess *mProcess = nullptr;
};
