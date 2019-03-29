/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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
#include "adblockinterceptor_debug.h"
#include "adblockutil.h"
#include "adblockinterceptor_debug.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include <KConfig>
#include <KConfigGroup>
#include <QDateTime>
#include <QDir>
#include <QSaveFile>
#include <QStandardPaths>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>
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
    qDeleteAll(mSubscriptions);
    mSubscriptions.clear();
    const bool enabled = AdBlock::AdBlockSettings::self()->adBlockEnabled();
    if (!enabled) {
        return;
    }
    KConfig config(QStringLiteral("AdBlockadblockrc"));
    KConfigGroup general = config.group(QStringLiteral("General"));

    mDisabledRules = general.readEntry(QStringLiteral("disabledRules"), QStringList());
    //Clear subscription
    QDir adblockDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/adblock"));
    // Create if necessary
    if (!adblockDir.exists()) {
        QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)).mkdir(QStringLiteral("adblock"));
    }

    for (const QString &fileName : adblockDir.entryList(QStringList() << QStringLiteral("*.txt"), QDir::Files)) {
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

    mCustomList = new AdBlockCustomList(this);
    mSubscriptions.append(mCustomList);
    // Load all subscriptions
    for (AdBlockSubscription *subscription : qAsConst(mSubscriptions)) {
        subscription->loadSubscription(mDisabledRules);
        connect(subscription, &AdBlockSubscription::subscriptionChanged, this, &AdblockManager::updateMatcher);
    }
    if (!mSubscriptions.isEmpty()) {
        const QDateTime lastUpdate = general.readEntry(QStringLiteral("lastUpdate"), QDateTime());
        if (lastUpdate.addDays(AdBlock::AdBlockSettings::self()->adBlockUpdateInterval()) < QDateTime::currentDateTime()) {
            QTimer::singleShot(1000 * 60, this, &AdblockManager::updateAllSubscriptions);
        }
    }
}

void AdblockManager::save()
{
    KConfig config(QStringLiteral("AdBlockadblockrc"));
    KConfigGroup general = config.group(QStringLiteral("General"));
    general.writeEntry(QStringLiteral("disabledRules"), mDisabledRules);

    for (AdBlockSubscription *subscription : qAsConst(mSubscriptions)) {
        subscription->saveSubscription();
    }
}

QStringList AdblockManager::disabledRules() const
{
    return mDisabledRules;
}

void AdblockManager::removeDisabledRule(const QString &filter)
{
    mDisabledRules.removeOne(filter);
}

void AdblockManager::addDisabledRule(const QString &filter)
{
    mDisabledRules.append(filter);
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

    qCDebug(ADBLOCKINTERCEPTOR_LOG) << " urlString" << urlString;
    const AdBlockRule *blockedRule = mAdBlockMatcher->match(info, host, urlString);
    if (blockedRule) {
        result = true;
        qCDebug(ADBLOCKINTERCEPTOR_LOG) << " blocked !!!!!!!!!!!!" << blockedRule->filter();
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

void AdblockManager::updateAllSubscriptions()
{
    for (AdBlockSubscription *subscription : qAsConst(mSubscriptions)) {
        subscription->updateSubscription();
    }

    KConfig config(QStringLiteral("AdBlockadblockrc"));
    KConfigGroup general = config.group(QStringLiteral("General"));
    general.writeEntry(QStringLiteral("lastUpdate"), QDateTime::currentDateTime());
}

AdBlockSubscription *AdblockManager::addSubscription(const QString &title, const QString &url)
{
    if (title.isEmpty() || url.isEmpty()) {
        return nullptr;
    }

    QString fileName = AdBlock::AdblockUtil::filterCharsFromFilename(title.toLower()) + QStringLiteral(".txt");
    QString filePath = AdBlock::AdblockUtil::ensureUniqueFilename(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/adblock/") + fileName);


    QByteArray data = QStringLiteral("Title: %1\nUrl: %2\n[Adblock Plus 1.1.1]").arg(title, url).toUtf8();

    QSaveFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockManager: Cannot write to file" << filePath;
        return nullptr;
    }
    file.write(data);
    file.commit();

    AdBlockSubscription *subscription = new AdBlockSubscription(title, this);
    subscription->setUrl(QUrl(url));
    subscription->setFilePath(filePath);
    subscription->loadSubscription(mDisabledRules);

    mSubscriptions.append(subscription);
    connect(subscription, &AdBlockSubscription::subscriptionChanged, this, &AdblockManager::updateMatcher);

    return subscription;
}

void AdblockManager::updateMatcher()
{
    mAdBlockMatcher->update();
}

bool AdblockManager::removeSubscription(AdBlockSubscription *subscription)
{
    if (!mSubscriptions.contains(subscription) || !subscription->canBeRemoved()) {
        return false;
    }

    QFile(subscription->filePath()).remove();
    mSubscriptions.removeOne(subscription);

    mAdBlockMatcher->update();
    delete subscription;

    return true;
}

void AdblockManager::addCustomRule(const QString &filter)
{
    AdBlockRule *rule = new AdBlockRule(filter, mCustomList);
    mCustomList->addRule(rule);
    mCustomList->saveSubscription();
    updateMatcher();
}
