/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antivirusplugin.h"
#include "antivirusplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AntiVirusPlugin, "kmail_antivirusplugin.json")

AntiVirusPlugin::AntiVirusPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

AntiVirusPlugin::~AntiVirusPlugin() = default;

PimCommon::GenericPluginInterface *AntiVirusPlugin::createInterface(QObject *parent)
{
    return new AntiVirusPluginInterface(parent);
}

#include "antivirusplugin.moc"
