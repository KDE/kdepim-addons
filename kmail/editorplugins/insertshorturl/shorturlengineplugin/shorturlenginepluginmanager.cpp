/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlengineplugin.h"
#include "shorturlenginepluginmanager.h"

#include <QFileInfo>
#include <QVector>
#include <KPluginMetaData>
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
    explicit ShortUrlEnginePluginManagerPrivate(ShortUrlEnginePluginManager *qq)
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
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("pimcommon/shorturlengine"));

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
