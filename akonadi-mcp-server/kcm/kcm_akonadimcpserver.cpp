/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcm_akonadimcpserver.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpProtocolServerConfigureWidget>

K_PLUGIN_CLASS_WITH_JSON(AkonadiMCPServerConfigurationModule, "kcm_akonadimcpserver.json")
using namespace Qt::Literals::StringLiterals;
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
    KSharedConfigPtr config = KSharedConfig::openConfig(u"akonadimcpprotocolrc"_s);
    KConfigGroup group = config->group(u"General"_s);
    group.writeEntry("Enabled", mEnabled->isChecked());

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::saveSettings(config, mMcpProtocolServerConfigureWidget->settings());
    KCModule::save();
}

void AkonadiMCPServerConfigurationModule::load()
{
    KSharedConfigPtr config = KSharedConfig::openConfig(u"akonadimcpprotocolrc"_s);
    KConfigGroup group = config->group(u"General"_s);

    mEnabled->setChecked(group.readEntry("Enabled", false));

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::loadSettings(config,
                                                                              this,
                                                                              [this](const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings) {
                                                                                  mMcpProtocolServerConfigureWidget->setSettings(settings);
                                                                                  setNeedsSave(false);
                                                                              });
    KCModule::load();
}

void AkonadiMCPServerConfigurationModule::defaults()
{
    mEnabled->setChecked(false);
    mMcpProtocolServerConfigureWidget->setSettings({});
}

#include "kcm_akonadimcpserver.moc"

#include "moc_kcm_akonadimcpserver.cpp"
