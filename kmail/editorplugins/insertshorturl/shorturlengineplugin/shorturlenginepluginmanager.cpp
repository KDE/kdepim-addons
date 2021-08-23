/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlenginepluginmanager.h"
#include "kcoreaddons_version.h"
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
    KPluginMetaData data;
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
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 86, 0)
    const QVector<KPluginMetaData> plugins = KPluginLoader::findPlugins(QStringLiteral("pimcommon/shorturlengine"));
#else
    const QVector<KPluginMetaData> plugins = KPluginMetaData::findPlugins(QStringLiteral("pimcommon/shorturlengine"));
#endif

    QVectorIterator<KPluginMetaData> i(plugins);
    i.toBack();
    while (i.hasPrevious()) {
        ShortUrlEnginePluginInfo info;
        const KPluginMetaData data = i.previous();
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.pluginName = data.name();
        info.data = data;

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
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(5, 85, 0)
    KPluginLoader pluginLoader(item->metaDataFileName);
    if (pluginLoader.factory()) {
        item->plugin = pluginLoader.factory()->create<ShortUrlEnginePlugin>(q, QVariantList() << item->metaDataFileNameBaseName);
        item->plugin->setPluginName(item->pluginName);
    }
#else
    if (auto plugin = KPluginFactory::instantiatePlugin<ShortUrlEnginePlugin>(item->data, q, QVariantList() << item->metaDataFileNameBaseName).plugin) {
        item->plugin = plugin;
        item->plugin->setPluginName(item->pluginName);
    }
#endif
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
