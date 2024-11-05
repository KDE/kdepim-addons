/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapactivitiesplugin.h"
#include <KPluginFactory>
#include <PimCommonActivities/ConfigureActivitiesWidget>
#include <QVBoxLayout>
K_PLUGIN_CLASS_WITH_JSON(LdapActivitiesPlugin, "kmailtransportactivities.json")

LdapActivitiesPlugin::LdapActivitiesPlugin(QWidget *widget, const QList<QVariant> &)
    : MailTransport::TransportActivitiesAbstractPlugin{widget}
    , mConfigureActivitiesWidget(new PimCommonActivities::ConfigureActivitiesWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->addWidget(mConfigureActivitiesWidget);
}

LdapActivitiesPlugin::~LdapActivitiesPlugin() = default;

MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings LdapActivitiesPlugin::activitiesSettings() const
{
    const auto settings = mConfigureActivitiesWidget->activitiesSettings();
    const MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings mailtransportSettings{
        settings.activities,
        settings.enabled,
    };
    return mailtransportSettings;
}

void LdapActivitiesPlugin::setActivitiesSettings(const ActivitySettings &activitySettings)
{
    const PimCommonActivities::ActivitiesBaseManager::ActivitySettings mailtransportSettings{
        activitySettings.activities,
        activitySettings.enabled,
    };
    mConfigureActivitiesWidget->setActivitiesSettings(mailtransportSettings);
}

#include "moc_ldapactivitiesplugin.cpp"
#include "transportactivitiesplugin.moc"
