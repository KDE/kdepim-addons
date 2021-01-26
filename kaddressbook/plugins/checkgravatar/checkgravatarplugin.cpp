/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkgravatarplugin.h"
#include "checkgravatarplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CheckGravatarPlugin, "kaddressbook_checkgravatarplugin.json")

CheckGravatarPlugin::CheckGravatarPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

CheckGravatarPlugin::~CheckGravatarPlugin()
{
}

PimCommon::GenericPluginInterface *CheckGravatarPlugin::createInterface(QObject *parent)
{
    auto *interface = new CheckGravatarPluginInterface(parent);
    return interface;
}

bool CheckGravatarPlugin::hasPopupMenuSupport() const
{
    return true;
}

#include "checkgravatarplugin.moc"
