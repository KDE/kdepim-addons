/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    SendMailPluginInterface *interface = new SendMailPluginInterface(parent);
    return interface;
}

bool SendMailPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "sendmailplugin.moc"
