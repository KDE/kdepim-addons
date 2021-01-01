/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

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

AntiVirusPlugin::~AntiVirusPlugin()
{
}

PimCommon::GenericPluginInterface *AntiVirusPlugin::createInterface(QObject *parent)
{
    auto *interface = new AntiVirusPluginInterface(parent);
    return interface;
}

#include "antivirusplugin.moc"
