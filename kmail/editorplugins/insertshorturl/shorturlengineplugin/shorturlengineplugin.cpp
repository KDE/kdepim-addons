/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlengineplugin.h"
using namespace Qt::Literals::StringLiterals;

ShortUrlEnginePlugin::ShortUrlEnginePlugin(QObject *parent)
    : QObject(parent)
{
}

ShortUrlEnginePlugin::~ShortUrlEnginePlugin() = default;

QString ShortUrlEnginePlugin::pluginName() const
{
    return mName;
}

void ShortUrlEnginePlugin::setPluginName(const QString &pluginname)
{
    mName = pluginname;
}

#include "moc_shorturlengineplugin.cpp"
