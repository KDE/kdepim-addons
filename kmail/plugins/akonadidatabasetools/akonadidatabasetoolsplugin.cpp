/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolsplugin.h"
#include "akonadidatabasetoolsplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AkonadiDatabaseToolsPlugin, "kmail_akonadidatabasetoolsplugin.json")

AkonadiDatabaseToolsPlugin::AkonadiDatabaseToolsPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

AkonadiDatabaseToolsPlugin::~AkonadiDatabaseToolsPlugin() = default;

PimCommon::GenericPluginInterface *AkonadiDatabaseToolsPlugin::createInterface(QObject *parent)
{
    return new AkonadiDatabaseToolsPluginInterface(parent);
}

#include "akonadidatabasetoolsplugin.moc"

#include "moc_akonadidatabasetoolsplugin.cpp"
