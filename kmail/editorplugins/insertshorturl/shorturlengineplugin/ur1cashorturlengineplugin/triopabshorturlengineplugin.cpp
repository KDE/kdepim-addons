/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "triopabshorturlengineplugin.h"
using namespace Qt::Literals::StringLiterals;

#include "triopabshorturlengineinterface.h"
#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(TriopAbShortUrlEnginePluginFactory, "pimcommon_triopabshorturlengineplugin.json", registerPlugin<TriopAbShortUrlEnginePlugin>();)

TriopAbShortUrlEnginePlugin::TriopAbShortUrlEnginePlugin(QObject *parent, const QList<QVariant> &)
    : ShortUrlEnginePlugin(parent)
{
}

TriopAbShortUrlEnginePlugin::~TriopAbShortUrlEnginePlugin()
{
}

ShortUrlEngineInterface *TriopAbShortUrlEnginePlugin::createInterface(QObject *parent)
{
    return new TripAbShortUrlEngineInterface(this, parent);
}

QString TriopAbShortUrlEnginePlugin::engineName() const
{
    return u"triopabshorturl"_s;
}

#include "triopabshorturlengineplugin.moc"

#include "moc_triopabshorturlengineplugin.cpp"
