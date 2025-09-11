/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KJob>
#include <QObject>

class CheckFolderSizeAccountPluginOpenFolderJob : public KJob
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginOpenFolderJob(const QString &identifier, QObject *parent = nullptr);
    ~CheckFolderSizeAccountPluginOpenFolderJob() override;

    void start() override;

private:
    const QString mIdentifer;
};
