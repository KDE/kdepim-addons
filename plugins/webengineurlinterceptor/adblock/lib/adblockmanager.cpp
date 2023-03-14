/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanager.h"
#include "adblockinterceptor_debug.h"
#include "adblockmatcher.h"
#include "adblocksubscription.h"
#include "adblockutil.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include <KConfig>
#include <KConfigGroup>
#include <QDateTime>
#include <QDir>
#include <QSaveFile>
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
    // Clear subscription
    QDir adblockDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/adblock"));
    // Create if necessary
    if (!adblockDir.exists()) {
        QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)).mkdir(QStringLiteral("adblock"));
    }

    const QStringList files = adblockDir.entryList(QStringList() << QStringLiteral("*.txt"), QDir::Files);
    for (const QString &fileName : files) {
        if (fileName == QLatin1String("customlist.txt")) {
            continue;
        }

        const QString absolutePath = adblockDir.absoluteFilePath(fileName);
        QFile file(absolutePath);
        if (!file.open(QFile::ReadOnly)) {
            continue;
        }

        QTextStream textStream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        textStream.setCodec("UTF-8");
#endif
        const QString title = textStream.readLine(1024).remove(QLatin1String("Title: "));
        const QUrl url = QUrl(textStream.readLine(1024).remove(QLatin1String("Url: ")));

        if (title.isEmpty() || !url.isValid()) {
            qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockManager: Invalid subscription file" << absolutePath;
            continue;
        }

        auto subscription = new AdBlockSubscription(title, this);
        subscription->setUrl(url);
        subscription->setFilePath(absolutePath);

        mSubscriptions.append(subscription);
    }

    mCustomList = new AdBlockCustomList(this);
    mSubscriptions.append(mCustomList);
    // Load all subscriptions
    for (AdBlockSubscription *subscription : std::as_const(mSubscriptions)) {
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

    for (AdBlockSubscription *subscription : std::as_const(mSubscriptions)) {
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

    if (scheme != QLatin1String("data")) { // may be long, so don't show in log
        qCDebug(ADBLOCKINTERCEPTOR_LOG) << " urlString" << urlString;
    }
    const AdBlockRule *blockedRule = mAdBlockMatcher->match(info, host, urlString);
    if (blockedRule) {
        result = true;
        qCDebug(ADBLOCKINTERCEPTOR_LOG) << " blocked !!!!!!!!!!!!" << blockedRule->filter();
        // TODO
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
    for (AdBlockSubscription *subscription : std::as_const(mSubscriptions)) {
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
    QString filePath = AdBlock::AdblockUtil::ensureUniqueFilename(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
                                                                  + QLatin1String("/adblock/") + fileName);

    QByteArray data = QStringLiteral("Title: %1\nUrl: %2\n[Adblock Plus 1.1.1]").arg(title, url).toUtf8();

    QSaveFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockManager: Cannot write to file" << filePath;
        return nullptr;
    }
    file.write(data);
    file.commit();

    auto subscription = new AdBlockSubscription(title, this);
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
    auto rule = new AdBlockRule(filter, mCustomList);
    mCustomList->addRule(rule);
    mCustomList->saveSubscription();
    updateMatcher();
}
