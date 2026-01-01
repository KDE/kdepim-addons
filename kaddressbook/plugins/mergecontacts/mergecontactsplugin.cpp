/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactsplugin.h"
#include "mergecontactsplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(MergeContactsPlugin, "kaddressbook_mergecontactsplugin.json")

MergeContactsPlugin::MergeContactsPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

MergeContactsPlugin::~MergeContactsPlugin() = default;

PimCommon::GenericPluginInterface *MergeContactsPlugin::createInterface(QObject *parent)
{
    return new MergeContactsPluginInterface(parent);
}

#include "mergecontactsplugin.moc"

#include "moc_mergecontactsplugin.cpp"
