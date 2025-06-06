/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MailTransport/TransportActivitiesAbstractPlugin>
namespace PimCommonActivities
{
class ConfigureActivitiesWidget;
}
class TransportActivitiesPlugin : public MailTransport::TransportActivitiesAbstractPlugin
{
    Q_OBJECT
public:
    explicit TransportActivitiesPlugin(QWidget *widget, const QList<QVariant> & = {});
    ~TransportActivitiesPlugin() override;

    [[nodiscard]] MailTransport::TransportActivitiesAbstractPlugin::ActivitySettings activitiesSettings() const override;
    void setActivitiesSettings(const ActivitySettings &activitySettings) override;

private:
    PimCommonActivities::ConfigureActivitiesWidget *const mConfigureActivitiesWidget;
};
