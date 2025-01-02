/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ur1cashorturlengineplugin.h"
#include "ur1cashorturlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(Ur1CaShortUrlEnginePluginFactory, "pimcommon_ur1cashorturlengineplugin.json", registerPlugin<Ur1CaShortUrlEnginePlugin>();)

Ur1CaShortUrlEnginePlugin::Ur1CaShortUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

Ur1CaShortUrlEnginePlugin::~Ur1CaShortUrlEnginePlugin()
{
}

ShortUrlEngineInterface *Ur1CaShortUrlEnginePlugin::createInterface(QObject *parent)
{
    return new Ur1CaShortUrlEngineInterface(this, parent);
}

QString Ur1CaShortUrlEnginePlugin::engineName() const
{
    return QStringLiteral("urlcashorturl");
}

#include "ur1cashorturlengineplugin.moc"

#include "moc_ur1cashorturlengineplugin.cpp"
