/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "antispamplugin.h"
#include "antispamplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AntiSpamPlugin, "kmail_antispamplugin.json")

AntiSpamPlugin::AntiSpamPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

AntiSpamPlugin::~AntiSpamPlugin() = default;

PimCommon::GenericPluginInterface *AntiSpamPlugin::createInterface(QObject *parent)
{
    return new AntiSpamPluginInterface(parent);
}

#include "antispamplugin.moc"

#include "moc_antispamplugin.cpp"
