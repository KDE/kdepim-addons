/*
   SPDX-FileCopyrightText: 2021 Alexander Lohnau <alexander.lohnau@gmx.de>
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>
   SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "kcm_gnupgsystemconfiguration.h"
#include <KPluginFactory>
#include <Libkleo/CryptoConfigModule>
#include <QGpgME/CryptoConfig>
#include <QGpgME/Protocol>
#include <QVBoxLayout>

K_PLUGIN_CLASS_WITH_JSON(GnuPGSystemConfigurationModule, "kcm_gnupgsystem.json")

GnuPGSystemConfigurationModule::GnuPGSystemConfigurationModule(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
{
    QGpgME::CryptoConfig *const config = QGpgME::cryptoConfig();
    mGnuPGSystemConfigurePage = new Kleo::CryptoConfigModule(config, widget());
    auto lay = new QVBoxLayout(widget());
    lay->setContentsMargins({});
    lay->addWidget(mGnuPGSystemConfigurePage);
    lay->addStretch(1);

    connect(mGnuPGSystemConfigurePage, &Kleo::CryptoConfigModule::changed, this, &GnuPGSystemConfigurationModule::slotConfigChanged);
}

GnuPGSystemConfigurationModule::~GnuPGSystemConfigurationModule()
{
    // ### correct here?
    if (QGpgME::CryptoConfig *const config = QGpgME::cryptoConfig()) {
        config->clear();
    }
}

void GnuPGSystemConfigurationModule::slotConfigChanged()
{
    markAsChanged();
}

void GnuPGSystemConfigurationModule::save()
{
    mGnuPGSystemConfigurePage->save();
}

void GnuPGSystemConfigurationModule::load()
{
    mGnuPGSystemConfigurePage->reset();
}

void GnuPGSystemConfigurationModule::defaults()
{
    mGnuPGSystemConfigurePage->defaults();
}

#include "kcm_gnupgsystemconfiguration.moc"

#include "moc_kcm_gnupgsystemconfiguration.cpp"
