/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include <KCModule>

class AkonadiMCPServerConfigurationModule : public KCModule
{
    Q_OBJECT
public:
    explicit AkonadiMCPServerConfigurationModule(QObject *parent, const KPluginMetaData &data);
    ~AkonadiMCPServerConfigurationModule() override;
    void load() override;
    void save() override;
    void defaults() override;

private:
    void slotConfigChanged();
};
