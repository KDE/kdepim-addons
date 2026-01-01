/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchduplicatesplugin.h"
#include "searchduplicatesplugininterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(SearchDuplicatesPlugin, "kaddressbook_searchduplicatesplugin.json")

SearchDuplicatesPlugin::SearchDuplicatesPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{
}

SearchDuplicatesPlugin::~SearchDuplicatesPlugin() = default;

PimCommon::GenericPluginInterface *SearchDuplicatesPlugin::createInterface(QObject *parent)
{
    return new SearchDuplicatesPluginInterface(parent);
}

#include "searchduplicatesplugin.moc"

#include "moc_searchduplicatesplugin.cpp"
