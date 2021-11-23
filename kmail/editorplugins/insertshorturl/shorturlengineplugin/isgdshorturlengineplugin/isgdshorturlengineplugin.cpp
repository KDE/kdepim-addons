/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "isgdshorturlengineplugin.h"
#include "isgdshorturlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(IsgdShortUrlEnginePlugin, "pimcommon_isgdshorturlengineplugin.json")

IsgdShortUrlEnginePlugin::IsgdShortUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

IsgdShortUrlEnginePlugin::~IsgdShortUrlEnginePlugin() = default;

ShortUrlEngineInterface *IsgdShortUrlEnginePlugin::createInterface(QObject *parent)
{
    return new IsgdShortUrlEngineInterface(this, parent);
}

QString IsgdShortUrlEnginePlugin::engineName() const
{
    return QStringLiteral("isdgshorturl");
}

#include "isgdshorturlengineplugin.moc"
