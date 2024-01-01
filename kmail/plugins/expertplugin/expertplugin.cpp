/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

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

ExpertPlugin::~ExpertPlugin() = default;

PimCommon::GenericPluginInterface *ExpertPlugin::createInterface(QObject *parent)
{
    return new ExpertPluginInterface(parent);
}

#include "expertplugin.moc"

#include "moc_expertplugin.cpp"
