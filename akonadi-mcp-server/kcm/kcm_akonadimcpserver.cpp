/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcm_akonadimcpserver.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>
#include <QCheckBox>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpProtocolServerConfigureWidget>

K_PLUGIN_CLASS_WITH_JSON(AkonadiMCPServerConfigurationModule, "kcm_akonadimcpserver.json")

AkonadiMCPServerConfigurationModule::AkonadiMCPServerConfigurationModule(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
    , mMcpProtocolServerConfigureWidget(new TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget(widget()))
    , mEnabled(new QCheckBox(i18n("Enabled"), widget()))
{
    auto lay = new QVBoxLayout(widget());
    lay->setContentsMargins({});
    lay->addWidget(mEnabled);
    lay->addWidget(mMcpProtocolServerConfigureWidget);
    lay->addStretch(1);

    connect(mMcpProtocolServerConfigureWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget::settingsChanged,
            this,
            &AkonadiMCPServerConfigurationModule::slotConfigChanged);
    connect(mEnabled, &QCheckBox::clicked, this, &AkonadiMCPServerConfigurationModule::slotConfigChanged);
}

AkonadiMCPServerConfigurationModule::~AkonadiMCPServerConfigurationModule() = default;

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
