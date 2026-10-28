/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcm_akonadimcpserver.h"
#include <KPluginFactory>
#include <QVBoxLayout>

K_PLUGIN_CLASS_WITH_JSON(AkonadiMCPServerConfigurationModule, "kcm_akonadimcpserver.json")

AkonadiMCPServerConfigurationModule::AkonadiMCPServerConfigurationModule(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
{
    auto lay = new QVBoxLayout(widget());
    lay->setContentsMargins({});
    // lay->addWidget(mGnuPGSystemConfigurePage);
    lay->addStretch(1);

    // connect(mGnuPGSystemConfigurePage, &Kleo::CryptoConfigModule::changed, this, &AkonadiMCPServerConfigurationModule::slotConfigChanged);
}

AkonadiMCPServerConfigurationModule::~AkonadiMCPServerConfigurationModule()
{
}

void AkonadiMCPServerConfigurationModule::slotConfigChanged()
{
    markAsChanged();
}

void AkonadiMCPServerConfigurationModule::save()
{
    // mGnuPGSystemConfigurePage->save();
}

void AkonadiMCPServerConfigurationModule::load()
{
    // mGnuPGSystemConfigurePage->reset();
}

void AkonadiMCPServerConfigurationModule::defaults()
{
    // mGnuPGSystemConfigurePage->defaults();
}

#include "kcm_akonadimcpserver.moc"

#include "moc_kcm_akonadimcpserver.cpp"
