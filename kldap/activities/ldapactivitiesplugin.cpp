/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapactivitiesplugin.h"
#include <KPluginFactory>
#include <PimCommonActivities/ConfigureActivitiesWidget>
#include <QVBoxLayout>
K_PLUGIN_CLASS_WITH_JSON(LdapActivitiesPlugin, "ldapactivitiesplugin.json")

LdapActivitiesPlugin::LdapActivitiesPlugin(QWidget *widget, const QList<QVariant> &)
    : KLDAPWidgets::LdapActivitiesAbstractPlugin{widget}
    , mConfigureActivitiesWidget(new PimCommonActivities::ConfigureActivitiesWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->addWidget(mConfigureActivitiesWidget);
}

LdapActivitiesPlugin::~LdapActivitiesPlugin() = default;

KLDAPWidgets::LdapActivitiesAbstractPlugin::ActivitySettings LdapActivitiesPlugin::activitiesSettings() const
{
    const auto settings = mConfigureActivitiesWidget->activitiesSettings();
    const KLDAPWidgets::LdapActivitiesAbstractPlugin::ActivitySettings ldapActivitySettings{
        settings.activities,
        settings.enabled,
    };
    return ldapActivitySettings;
}

void LdapActivitiesPlugin::setActivitiesSettings(const ActivitySettings &activitySettings)
{
    const PimCommonActivities::ActivitiesBaseManager::ActivitySettings ldapActivitySettings{
        activitySettings.activities,
        activitySettings.enabled,
    };
    mConfigureActivitiesWidget->setActivitiesSettings(ldapActivitySettings);
}

#include "ldapactivitiesplugin.moc"
#include "moc_ldapactivitiesplugin.cpp"
