/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "shorturlengineplugin.h"
#include "shorturlenginepluginmanager.h"

#include <QFileInfo>
#include <QVector>
#include <kpluginmetadata.h>
#include <KPluginLoader>
#include <KPluginFactory>
#include <QSet>

class ShortUrlEnginePluginInfo
{
public:
    ShortUrlEnginePluginInfo()
        : plugin(nullptr)
    {
    }

    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    QString pluginName;
    ShortUrlEnginePlugin *plugin = nullptr;
};

class ShortUrlEnginePluginManagerPrivate
{
public:
    ShortUrlEnginePluginManagerPrivate(ShortUrlEnginePluginManager *qq)
        : q(qq)
    {
    }

    void initializePlugins();
    void loadPlugin(ShortUrlEnginePluginInfo *item);
    QVector<ShortUrlEnginePlugin *> pluginsList() const;
    QVector<ShortUrlEnginePluginInfo> mPluginList;
    ShortUrlEnginePluginManager *q;
};

void ShortUrlEnginePluginManagerPrivate::initializePlugins()
{
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("pimcommon"), [](const KPluginMetaData &md) {
        return md.serviceTypes().contains(QStringLiteral("PimCommonShortUrlEngine/Plugin"));
    });

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        ShortUrlEnginePluginInfo info;
        const KPluginMetaData data = i.previous();
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.pluginName = data.name();

        // only load plugins once, even if found multiple times!
        if (unique.contains(info.metaDataFileNameBaseName)) {
            continue;
        }
        info.plugin = nullptr;
        mPluginList.push_back(info);
        unique.insert(info.metaDataFileNameBaseName);
    }
    QVector<ShortUrlEnginePluginInfo>::iterator end(mPluginList.end());
    for (QVector<ShortUrlEnginePluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
}

void ShortUrlEnginePluginManagerPrivate::loadPlugin(ShortUrlEnginePluginInfo *item)
{
    KPluginLoader pluginLoader(item->metaDataFileName);
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<ShortUrlEnginePlugin>(q, QVariantList() << item->metaDataFileNameBaseName);
        item->plugin->setPluginName(item->pluginName);
    }
}

QVector<ShortUrlEnginePlugin *> ShortUrlEnginePluginManagerPrivate::pluginsList() const
{
    QVector<ShortUrlEnginePlugin *> lst;
    QVector<ShortUrlEnginePluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QVector<ShortUrlEnginePluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if ((*it).plugin) {
            lst << (*it).plugin;
        }
    }
    return lst;
}

ShortUrlEnginePluginManager::ShortUrlEnginePluginManager(QObject *parent)
    : QObject(parent)
    , d(new ShortUrlEnginePluginManagerPrivate(this))
{
    d->initializePlugins();
}

ShortUrlEnginePluginManager::~ShortUrlEnginePluginManager()
{
    delete d;
}

ShortUrlEnginePluginManager *ShortUrlEnginePluginManager::self()
{
    static ShortUrlEnginePluginManager s_self;
    return &s_self;
}

QVector<ShortUrlEnginePlugin *> ShortUrlEnginePluginManager::pluginsList() const
{
    return d->pluginsList();
}
