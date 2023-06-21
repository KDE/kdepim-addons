/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "tinyurlengineplugin.h"
#include "tinyurlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(TinyUrlEnginePlugin, "pimcommon_tinyurlengineplugin.json")

TinyUrlEnginePlugin::TinyUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

TinyUrlEnginePlugin::~TinyUrlEnginePlugin() = default;

ShortUrlEngineInterface *TinyUrlEnginePlugin::createInterface(QObject *parent)
{
    return new TinyUrlEngineInterface(this, parent);
}

QString TinyUrlEnginePlugin::engineName() const
{
    return QStringLiteral("tinyurl");
}

#include "tinyurlengineplugin.moc"

#include "moc_tinyurlengineplugin.cpp"
