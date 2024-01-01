/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "triopabshorturlengineplugin.h"
#include "triopabshorturlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(TriopAbShortUrlEnginePlugin, "pimcommon_triopabshorturlengineplugin.json")

TriopAbShortUrlEnginePlugin::TriopAbShortUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

TriopAbShortUrlEnginePlugin::~TriopAbShortUrlEnginePlugin() = default;

ShortUrlEngineInterface *TriopAbShortUrlEnginePlugin::createInterface(QObject *parent)
{
    return new TripAbShortUrlEngineInterface(this, parent);
}

QString TriopAbShortUrlEnginePlugin::engineName() const
{
    return QStringLiteral("triopabshorturl");
}

#include "triopabshorturlengineplugin.moc"

#include "moc_triopabshorturlengineplugin.cpp"
