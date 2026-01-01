/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendvcardsplugin.h"
#include "sendvcardsplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(SendVcardsPlugin, "kaddressbook_sendvcardsplugin.json")

SendVcardsPlugin::SendVcardsPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

SendVcardsPlugin::~SendVcardsPlugin() = default;

PimCommon::GenericPluginInterface *SendVcardsPlugin::createInterface(QObject *parent)
{
    return new SendVcardsPluginInterface(parent);
}

bool SendVcardsPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "sendvcardsplugin.moc"

#include "moc_sendvcardsplugin.cpp"
