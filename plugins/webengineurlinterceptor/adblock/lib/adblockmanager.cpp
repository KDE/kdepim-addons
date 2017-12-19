/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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
#include "globalsettings_webengineurlinterceptoradblock.h"
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
}

void AdblockManager::reloadConfig()
{
    loadSubscriptions();
    bool enabled = AdBlock::AdBlockSettings::self()->adBlockEnabled();
    Q_EMIT enabledChanged(enabled);
}

void AdblockManager::loadSubscriptions()
{
    //Clear subscription
    mSubscriptions.clear();
    //TODO load element

}

void AdblockManager::removeDisabledRule(const QString &filter)
{

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
