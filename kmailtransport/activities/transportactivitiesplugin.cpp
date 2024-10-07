/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

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

#include "transportactivitiesplugin.moc"

#include "moc_transportactivitiesplugin.cpp"
