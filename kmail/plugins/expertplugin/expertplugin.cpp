/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

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
    return new ExpertPluginInterface(parent);
}

#include "expertplugin.moc"
