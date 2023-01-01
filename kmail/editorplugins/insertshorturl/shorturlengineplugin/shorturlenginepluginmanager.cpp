/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlenginepluginmanager.h"
#include "shorturlengineplugin.h"
#include <KPluginFactory>
#include <KPluginMetaData>
#include <QFileInfo>
#include <QVector>

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
    Q_REQUIRED_RESULT QVector<ShortUrlEnginePlugin *> pluginsList() const;
    QVector<ShortUrlEnginePluginInfo> mPluginList;
    ShortUrlEnginePluginManager *const q;
};

void ShortUrlEnginePluginManagerPrivate::initializePlugins()
{
    const QVector<KPluginMetaData> plugins =
        KPluginMetaData::findPlugins(QStringLiteral("pim" QT_STRINGIFY(QT_VERSION_MAJOR)) + QStringLiteral("/pimcommon/shorturlengine"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QVectorIterator<KPluginMetaData> i(plugins);
#else
    QListIterator<KPluginMetaData> i(plugins);
#endif
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
    const QVector<ShortUrlEnginePluginInfo>::iterator end(mPluginList.end());
    for (QVector<ShortUrlEnginePluginInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
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

ShortUrlEnginePluginManager::~ShortUrlEnginePluginManager() = default;

ShortUrlEnginePluginManager *ShortUrlEnginePluginManager::self()
{
    static ShortUrlEnginePluginManager s_self;
    return &s_self;
}

QVector<ShortUrlEnginePlugin *> ShortUrlEnginePluginManager::pluginsList() const
{
    return d->pluginsList();
}
