/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlenginepluginmanager.h"
#include "shorturlengineplugin.h"

#include <KPluginFactory>
#include <KPluginLoader>
#include <KPluginMetaData>
#include <QFileInfo>
#include <QSet>
#include <QVector>

class ShortUrlEnginePluginInfo
{
public:
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    QString pluginName;
    ShortUrlEnginePlugin *plugin = nullptr;
};

class ShortUrlEnginePluginManagerPrivate
{
public:
    explicit ShortUrlEnginePluginManagerPrivate(ShortUrlEnginePluginManager *qq)
        : q(qq)
    {
    }

    void initializePlugins();
    void loadPlugin(ShortUrlEnginePluginInfo *item);
    QVector<ShortUrlEnginePlugin *> pluginsList() const;
    QVector<ShortUrlEnginePluginInfo> mPluginList;
    ShortUrlEnginePluginManager *const q;
};

void ShortUrlEnginePluginManagerPrivate::initializePlugins()
{
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("pimcommon/shorturlengine"));

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    while (i.hasPrevious()) {
        ShortUrlEnginePluginInfo info;
        const KPluginMetaData data = i.previous();
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.pluginName = data.name();

        info.plugin = nullptr;
        mPluginList.push_back(info);
    }
    const QVector<ShortUrlEnginePluginInfo>::iterator end(mPluginList.end());
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
