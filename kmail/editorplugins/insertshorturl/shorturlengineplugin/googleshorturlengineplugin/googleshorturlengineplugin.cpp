/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleshorturlengineplugin.h"
#include "googleshorturlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(GoogleShortUrlEnginePluginFactory, "pimcommon_googleshorturlengineplugin.json", registerPlugin<GoogleShortUrlEnginePlugin>();)

GoogleShortUrlEnginePlugin::GoogleShortUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

GoogleShortUrlEnginePlugin::~GoogleShortUrlEnginePlugin()
{
}

ShortUrlEngineInterface *GoogleShortUrlEnginePlugin::createInterface(QObject *parent)
{
    return new GoogleShortUrlEngineInterface(parent);
}

#include "googleshorturlengineplugin.moc"

#include "moc_googleshorturlengineplugin.cpp"
