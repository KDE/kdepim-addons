/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KLDAPWidgets/LdapActivitiesAbstractPlugin>
namespace PimCommonActivities
{
class ConfigureActivitiesWidget;
}
class LdapActivitiesPlugin : public KLDAPWidgets::LdapActivitiesAbstractPlugin
{
    Q_OBJECT
public:
    explicit LdapActivitiesPlugin(QWidget *widget, const QList<QVariant> & = {});
    ~LdapActivitiesPlugin() override;

    [[nodiscard]] KLDAPWidgets::LdapActivitiesAbstractPlugin::ActivitySettings activitiesSettings() const override;
    void setActivitiesSettings(const ActivitySettings &activitySettings) override;

private:
    PimCommonActivities::ConfigureActivitiesWidget *const mConfigureActivitiesWidget;
};
