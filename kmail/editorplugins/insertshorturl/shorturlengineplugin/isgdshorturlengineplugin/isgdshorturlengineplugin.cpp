/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "isgdshorturlengineplugin.h"
using namespace Qt::Literals::StringLiterals;

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
    return u"isdgshorturl"_s;
}

#include "isgdshorturlengineplugin.moc"

#include "moc_isgdshorturlengineplugin.cpp"
