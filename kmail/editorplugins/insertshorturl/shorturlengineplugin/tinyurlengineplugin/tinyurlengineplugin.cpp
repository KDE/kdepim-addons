/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "tinyurlengineplugin.h"
using namespace Qt::Literals::StringLiterals;

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
    return u"tinyurl"_s;
}

#include "tinyurlengineplugin.moc"

#include "moc_tinyurlengineplugin.cpp"
