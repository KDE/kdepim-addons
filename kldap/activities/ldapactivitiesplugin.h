/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MailTransport/TransportActivitiesAbstractPlugin>
namespace PimCommonActivities
{
class ConfigureActivitiesWidget;
}
class LdapActivitiesPlugin : public MailTransport::TransportActivitiesAbstractPlugin
{
    Q_OBJECT
public:
    explicit LdapActivitiesPlugin(QWidget *widget, const QList<QVariant> & = {});
    ~LdapActivitiesPlugin() override;

    [[nodiscard]] MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings activitiesSettings() const override;
    void setActivitiesSettings(const ActivitySettings &activitySettings) override;

private:
    PimCommonActivities::ConfigureActivitiesWidget *const mConfigureActivitiesWidget;
};
