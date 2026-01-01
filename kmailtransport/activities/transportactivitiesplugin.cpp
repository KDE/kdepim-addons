/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "transportactivitiesplugin.h"
#include <KPluginFactory>
#include <PimCommonActivities/ConfigureActivitiesWidget>
#include <QVBoxLayout>
K_PLUGIN_CLASS_WITH_JSON(TransportActivitiesPlugin, "kmailtransportactivities.json")

TransportActivitiesPlugin::TransportActivitiesPlugin(QWidget *widget, const QList<QVariant> &)
    : MailTransport::TransportActivitiesAbstractPlugin{widget}
    , mConfigureActivitiesWidget(new PimCommonActivities::ConfigureActivitiesWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->addWidget(mConfigureActivitiesWidget);
}

TransportActivitiesPlugin::~TransportActivitiesPlugin() = default;

MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings TransportActivitiesPlugin::activitiesSettings() const
{
    const auto settings = mConfigureActivitiesWidget->activitiesSettings();
    const MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings mailtransportSettings{
        settings.activities,
        settings.enabled,
    };
    return mailtransportSettings;
}

void TransportActivitiesPlugin::setActivitiesSettings(const ActivitySettings &activitySettings)
{
    const PimCommonActivities::ActivitiesBaseManager::ActivitySettings mailtransportSettings{
        activitySettings.activities,
        activitySettings.enabled,
    };
    mConfigureActivitiesWidget->setActivitiesSettings(mailtransportSettings);
}

#include "moc_transportactivitiesplugin.cpp"
#include "transportactivitiesplugin.moc"
