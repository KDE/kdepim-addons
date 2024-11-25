/*
   SPDX-FileCopyrightText: 2021 Alexander Lohnau <alexander.lohnau@gmx.de>
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>
   SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/
#pragma once
#include <KCModule>
namespace Kleo
{
class CryptoConfigModule;
}

class GnuPGSystemConfigurationModule : public KCModule
{
    Q_OBJECT
public:
    explicit GnuPGSystemConfigurationModule(QObject *parent, const KPluginMetaData &data);
    ~GnuPGSystemConfigurationModule() override;
    void load() override;
    void save() override;
    void defaults() override;

private:
    void slotConfigChanged();
    Kleo::CryptoConfigModule *mGnuPGSystemConfigurePage = nullptr;
};
