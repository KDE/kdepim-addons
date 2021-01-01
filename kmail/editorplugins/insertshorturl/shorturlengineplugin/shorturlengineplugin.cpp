/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlengineplugin.h"

ShortUrlEnginePlugin::ShortUrlEnginePlugin(QObject *parent)
    : QObject(parent)
{
}

ShortUrlEnginePlugin::~ShortUrlEnginePlugin()
{
}

QString ShortUrlEnginePlugin::pluginName() const
{
    return mName;
}

void ShortUrlEnginePlugin::setPluginName(const QString &pluginname)
{
    mName = pluginname;
}
