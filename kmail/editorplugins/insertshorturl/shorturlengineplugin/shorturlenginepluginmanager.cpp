/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlenginepluginmanager.h"
using namespace Qt::Literals::StringLiterals;

#include "shorturlengineplugin.h"
#include <KPluginFactory>
#include <KPluginMetaData>
#include <QFileInfo>
#include <QList>

class ShortUrlEnginePluginInfo
{
public:
    KPluginMetaData data;
    QString metaDataFileNameBaseName;
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
    [[nodiscard]] QList<ShortUrlEnginePlugin *> pluginsList() const;
    QList<ShortUrlEnginePluginInfo> mPluginList;
    ShortUrlEnginePluginManager *const q;
};

void ShortUrlEnginePluginManagerPrivate::initializePlugins()
{
    const QList<KPluginMetaData> plugins = KPluginMetaData::findPlugins(u"pim6/pimcommon/shorturlengine"_s);

    QListIterator<KPluginMetaData> i(plugins);
    i.toBack();
    while (i.hasPrevious()) {
        ShortUrlEnginePluginInfo info;
        const KPluginMetaData data = i.previous();
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.pluginName = data.name();
        info.data = data;

        info.plugin = nullptr;
        mPluginList.push_back(info);
    }
    const QList<ShortUrlEnginePluginInfo>::iterator end(mPluginList.end());
    for (QList<ShortUrlEnginePluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
}

void ShortUrlEnginePluginManagerPrivate::loadPlugin(ShortUrlEnginePluginInfo *item)
{
    if (auto plugin = KPluginFactory::instantiatePlugin<ShortUrlEnginePlugin>(item->data, q, QVariantList() << item->metaDataFileNameBaseName).plugin) {
        item->plugin = plugin;
        item->plugin->setPluginName(item->pluginName);
    }
}

QList<ShortUrlEnginePlugin *> ShortUrlEnginePluginManagerPrivate::pluginsList() const
{
    QList<ShortUrlEnginePlugin *> lst;
    QList<ShortUrlEnginePluginInfo>::ConstIterator end(mPluginList.constEnd());
    for (QList<ShortUrlEnginePluginInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
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

ShortUrlEnginePluginManager::~ShortUrlEnginePluginManager() = default;

ShortUrlEnginePluginManager *ShortUrlEnginePluginManager::self()
{
    static ShortUrlEnginePluginManager s_self;
    return &s_self;
}

QList<ShortUrlEnginePlugin *> ShortUrlEnginePluginManager::pluginsList() const
{
    return d->pluginsList();
}

#include "moc_shorturlenginepluginmanager.cpp"
