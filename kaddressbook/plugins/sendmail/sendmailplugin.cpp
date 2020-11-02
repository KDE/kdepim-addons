/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendmailplugin.h"
#include "sendmailplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(SendMailPlugin, "kaddressbook_sendmailplugin.json")

SendMailPlugin::SendMailPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

SendMailPlugin::~SendMailPlugin()
{
}

PimCommon::GenericPluginInterface *SendMailPlugin::createInterface(QObject *parent)
{
    auto *interface = new SendMailPluginInterface(parent);
    return interface;
}

bool SendMailPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "sendmailplugin.moc"
