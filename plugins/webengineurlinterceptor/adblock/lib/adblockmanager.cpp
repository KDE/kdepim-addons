/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#include "adblockmanager.h"
#include "adblockmatcher.h"
#include "adblocksubscription.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include <QDir>
#include <QTextStream>
#include <QUrl>

using namespace AdBlock;

AdblockManager *AdblockManager::self()
{
    static AdblockManager s_self;
    return &s_self;
}

AdblockManager::AdblockManager(QObject *parent)
    : QObject(parent)
{
    mAdBlockMatcher = new AdBlockMatcher(this);
    reloadConfig();
}

AdblockManager::~AdblockManager()
{
    qDeleteAll(mSubscriptions);
}

void AdblockManager::reloadConfig()
{
    loadSubscriptions();
    const bool enabled = AdBlock::AdBlockSettings::self()->adBlockEnabled();
    Q_EMIT enabledChanged(enabled);
}

void AdblockManager::loadSubscriptions()
{
    //Clear subscription
    qDeleteAll(mSubscriptions);
    mSubscriptions.clear();
#if 0
    QDir adblockDir(DataPaths::currentProfilePath() + "/adblock");
    // Create if neccessary
    if (!adblockDir.exists()) {
        QDir(DataPaths::currentProfilePath()).mkdir("adblock");
    }

    foreach (const QString &fileName, adblockDir.entryList(QStringList("*.txt"), QDir::Files)) {
        if (fileName == QLatin1String("customlist.txt")) {
            continue;
        }

        const QString absolutePath = adblockDir.absoluteFilePath(fileName);
        QFile file(absolutePath);
        if (!file.open(QFile::ReadOnly)) {
            continue;
        }

        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        QString title = textStream.readLine(1024).remove(QLatin1String("Title: "));
        QUrl url = QUrl(textStream.readLine(1024).remove(QLatin1String("Url: ")));

        if (title.isEmpty() || !url.isValid()) {
            qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockManager: Invalid subscription file" << absolutePath;
            continue;
        }

        AdBlockSubscription *subscription = new AdBlockSubscription(title, this);
        subscription->setUrl(url);
        subscription->setFilePath(absolutePath);

        mSubscriptions.append(subscription);
    }
 #endif
    // Prepend EasyList if subscriptions are empty
    if (mSubscriptions.isEmpty()) {
//         AdBlockSubscription* easyList = new AdBlockSubscription(tr("EasyList"), this);
//         easyList->setUrl(QUrl(ADBLOCK_EASYLIST_URL));
//         easyList->setFilePath(DataPaths::currentProfilePath() + QLatin1String("/adblock/easylist.txt"));

//         mSubscriptions.prepend(easyList);
    }

    //TODO load it
    // new AdBlockSubscription(...);
    // loadSubscription()
    //TODO load element
    // Append CustomList
    AdBlockCustomList *customList = new AdBlockCustomList(this);
    mSubscriptions.append(customList);
    // Load all subscriptions
    /*
    foreach (AdBlockSubscription* subscription, mSubscriptions) {
        subscription->loadSubscription(m_disabledRules);

    }
    */
}

void AdblockManager::save()
{
    foreach (AdBlockSubscription *subscription, mSubscriptions) {
        subscription->saveSubscription();
    }
}

void AdblockManager::removeDisabledRule(const QString &filter)
{
    //TODO
}

void AdblockManager::addDisabledRule(const QString &filter)
{
    //TODO
}

bool AdblockManager::isEnabled() const
{
    return mAdBlockMatcher->isEnabled();
}

bool AdblockManager::interceptRequest(const QWebEngineUrlRequestInfo &info)
{
    bool result = false;
    QUrl url = info.requestUrl();
    const QString urlString = url.toString().toLower();
    const QString host = url.host().toLower();
    const QString scheme = url.scheme().toLower();

    if (!canRunOnScheme(scheme)) {
        return result;
    }

    const AdBlockRule *blockedRule = mAdBlockMatcher->match(info, host, urlString);
    if (blockedRule) {
        result = true;
        //TODO
    }
    return result;
}

bool AdblockManager::canRunOnScheme(const QString &scheme) const
{
    return scheme != QLatin1String("file");
}

QList<AdBlockSubscription *> AdblockManager::subscriptions() const
{
    return mSubscriptions;
}
