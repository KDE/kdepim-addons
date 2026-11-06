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
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QProcess>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpProtocolServerConfigureWidget>

K_PLUGIN_CLASS_WITH_JSON(AkonadiMCPServerConfigurationModule, "kcm_akonadimcpserver.json")
using namespace Qt::Literals::StringLiterals;
AkonadiMCPServerConfigurationModule::AkonadiMCPServerConfigurationModule(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
    , mMcpProtocolServerConfigureWidget(new TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget(widget()))
    , mEnabled(new QCheckBox(i18n("Enabled"), widget()))
    , mConfirmModify(new QCheckBox(i18nc("@option:check", "Ask confirmation before running tools which modify data")))
{
    auto lay = new QVBoxLayout(widget());
    lay->addWidget(mEnabled);

    mConfirmModify->setObjectName(u"mConfirmModify"_s);
    lay->addWidget(mConfirmModify);

    lay->addWidget(mMcpProtocolServerConfigureWidget);
    lay->addStretch(1);

    connect(mMcpProtocolServerConfigureWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget::settingsChanged,
            this,
            &AkonadiMCPServerConfigurationModule::slotConfigChanged);
    connect(mEnabled, &QCheckBox::clicked, this, &AkonadiMCPServerConfigurationModule::slotConfigChanged);

    connect(mEnabled,
            &QCheckBox::toggled,
            mMcpProtocolServerConfigureWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget::setEnabled);
    connect(mEnabled, &QCheckBox::toggled, mConfirmModify, &QCheckBox::setEnabled);
    mConfirmModify->setEnabled(false);

    mMcpProtocolServerConfigureWidget->setEnabled(false);
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
    group.writeEntry("AskModify", mConfirmModify->isChecked());

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::saveSettings(config, mMcpProtocolServerConfigureWidget->settings());
    config->sync();
    reloadServer();
    KCModule::save();
}

void AkonadiMCPServerConfigurationModule::reloadServer()
{
    const QString serviceName = u"org.kde.akonadimcpprotocol"_s;
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (bus.interface()->isServiceRegistered(serviceName)) {
        const QDBusMessage msg = QDBusMessage::createMethodCall(serviceName, u"/"_s, serviceName, u"reload"_s);
        bus.asyncCall(msg);
    } else if (mEnabled->isChecked()) {
        QProcess::startDetached(u"akonadimcpprotocol"_s, {});
    }
}

void AkonadiMCPServerConfigurationModule::load()
{
    KSharedConfigPtr config = KSharedConfig::openConfig(u"akonadimcpprotocolrc"_s);
    KConfigGroup group = config->group(u"General"_s);

    mEnabled->setChecked(group.readEntry("Enabled", false));
    mConfirmModify->setChecked(group.readEntry("AskModify", true));

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
