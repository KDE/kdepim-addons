/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "logactivitiesplugin.h"
#include "logactivitiesplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(LogActivitiesPlugin, "kmail_logactivitiesplugin.json")

LogActivitiesPlugin::LogActivitiesPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

LogActivitiesPlugin::~LogActivitiesPlugin() = default;

PimCommon::GenericPluginInterface *LogActivitiesPlugin::createInterface(QObject *parent)
{
    return new LogActivitiesPluginInterface(parent);
}

#include "logactivitiesplugin.moc"
