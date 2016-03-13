/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "adblockmanager.h"
#include <QUrl>

using namespace AdBlock;

class AdblockManagerInstancePrivate
{
public:
    AdblockManagerInstancePrivate()
        : ablockManager(new AdblockManager)
    {
    }

    ~AdblockManagerInstancePrivate()
    {
        delete ablockManager;
    }

    AdblockManager *ablockManager;
};

Q_GLOBAL_STATIC(AdblockManagerInstancePrivate, sInstance)

AdblockManager *AdblockManager::self()
{
    return sInstance->ablockManager;
}

AdblockManager::AdblockManager(QObject *parent)
    : QObject(parent),
      mEnabled(false)
{
    reloadConfig();
}

AdblockManager::~AdblockManager()
{

}

void AdblockManager::reloadConfig()
{
    //TODO
}

bool AdblockManager::isEnabled() const
{
    return mEnabled;
}

bool AdblockManager::interceptRequest(const QWebEngineUrlRequestInfo &info)
{
    QUrl url = info.requestUrl();
    const QString urlString = url.toString().toLower();
    const QString host = url.host().toLower();
    const QString scheme = url.scheme().toLower();

    if (!canRunOnScheme(scheme)) {
        return false;
    }

    //TODO
    return false;
}

bool AdblockManager::canRunOnScheme(const QString &scheme) const
{
    return !(scheme == QLatin1String("file"));
}
