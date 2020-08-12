/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expertplugin.h"
#include "expertplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ExpertPlugin, "kmail_expertplugin.json")

ExpertPlugin::ExpertPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

ExpertPlugin::~ExpertPlugin()
{
}

PimCommon::GenericPluginInterface *ExpertPlugin::createInterface(QObject *parent)
{
    ExpertPluginInterface *interface = new ExpertPluginInterface(parent);
    return interface;
}

#include "expertplugin.moc"
