/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>
  SPDX-FileCopyrightText: 2009 Benjamin C. Meyer <ben@meyerhome.net>

  SPDX-License-Identifier: GPL-2.0-or-later OR BSD-3-Clause
*/

#include "adblocksubscription.h"
#include "adblockinterceptor_debug.h"
#include "adblockmanager.h"
#include "adblockutil.h"

#include <KLocalizedString>
#include <QFile>
#include <QNetworkReply>
#include <QSaveFile>
#include <QStandardPaths>
#include <QTimer>
using namespace AdBlock;

AdBlockSubscription::AdBlockSubscription(const QString &title, QObject *parent)
    : QObject(parent)
    , mTitle(title)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

QString AdBlockSubscription::title() const
{
    return mTitle;
}

QString AdBlockSubscription::filePath() const
{
    return mFilePath;
}

void AdBlockSubscription::setFilePath(const QString &path)
{
    mFilePath = path;
}

QUrl AdBlockSubscription::url() const
{
    return mUrl;
}

void AdBlockSubscription::setUrl(const QUrl &url)
{
    mUrl = url;
}

void AdBlockSubscription::loadSubscription(const QStringList &disabledRules)
{
    if (!enabled()) {
        return;
    }
    QFile file(mFilePath);
    // qCWarning(ADBLOCKINTERCEPTOR_LOG) << "loadSubscription:: loading path:" << mFilePath;
    if (!file.exists()) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    if (!file.open(QFile::ReadOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for reading" << mFilePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    QTextStream textStream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    textStream.setCodec("UTF-8");
#endif

    // Header is on 3rd line
    textStream.readLine(1024);
    textStream.readLine(1024);
    QString header = textStream.readLine(1024);

    if (!header.startsWith(QLatin1String("[Adblock")) || mTitle.isEmpty()) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "invalid format of adblock file" << mFilePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    mRules.clear();

    while (!textStream.atEnd()) {
        auto rule = new AdBlockRule(textStream.readLine(), this);
        if (disabledRules.contains(rule->filter())) {
            rule->setEnabled(false);
        }

        mRules.append(rule);
    }

    // Initial update
    if (mRules.isEmpty() && !mUpdated) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
    }
}

void AdBlockSubscription::saveSubscription()
{
}

void AdBlockSubscription::updateSubscription()
{
    if (mReply || !mUrl.isValid()) {
        return;
    }
    mReply = mNetworkAccessManager->get(QNetworkRequest(mUrl));

    connect(mReply, &QNetworkReply::finished, this, &AdBlockSubscription::subscriptionDownloaded);
}

void AdBlockSubscription::subscriptionDownloaded()
{
    if (mReply != qobject_cast<QNetworkReply *>(sender())) {
        return;
    }

    bool error = false;
    const QByteArray response = QString::fromUtf8(mReply->readAll()).toUtf8();

    if (mReply->error() != QNetworkReply::NoError || !response.startsWith(QByteArray("[Adblock")) || !saveDownloadedData(response)) {
        error = true;
    }

    mReply->deleteLater();
    mReply = nullptr;

    if (error) {
        Q_EMIT subscriptionError(i18n("Cannot load subscription!"));
        return;
    }

    loadSubscription(AdblockManager::self()->disabledRules());

    Q_EMIT subscriptionUpdated();
    Q_EMIT subscriptionChanged();
}

bool AdBlockSubscription::saveDownloadedData(const QByteArray &data)
{
    QSaveFile file(mFilePath);

    if (!file.open(QFile::WriteOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for writing:" << mFilePath;
        return false;
    }

    // Write subscription header
    file.write(QStringLiteral("Title: %1\nUrl: %2\n").arg(title(), url().toString()).toUtf8());
    file.write(data);
    file.commit();
    return true;
}

bool AdBlockSubscription::enabled() const
{
    return mEnabled;
}

void AdBlockSubscription::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

const AdBlockRule *AdBlockSubscription::rule(int offset) const
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    return mRules[offset];
}

QVector<AdBlockRule *> AdBlockSubscription::allRules() const
{
    return mRules;
}

const AdBlockRule *AdBlockSubscription::enableRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = mRules[offset];
    rule->setEnabled(true);
    AdblockManager::self()->removeDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();
    return rule;
}

const AdBlockRule *AdBlockSubscription::disableRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = mRules[offset];
    rule->setEnabled(false);
    AdblockManager::self()->addDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();

    return rule;
}

bool AdBlockSubscription::canEditRules() const
{
    return false;
}

bool AdBlockSubscription::canBeRemoved() const
{
    return true;
}

int AdBlockSubscription::addRule(AdBlockRule *rule)
{
    Q_UNUSED(rule)
    return -1;
}

bool AdBlockSubscription::removeRule(int offset)
{
    Q_UNUSED(offset)
    return false;
}

const AdBlockRule *AdBlockSubscription::replaceRule(AdBlockRule *rule, int offset)
{
    Q_UNUSED(rule)
    Q_UNUSED(offset)
    return nullptr;
}

AdBlockSubscription::~AdBlockSubscription()
{
    qDeleteAll(mRules);
}

// AdBlockCustomList

AdBlockCustomList::AdBlockCustomList(QObject *parent)
    : AdBlockSubscription(i18n("Custom Rules"), parent)
{
    setFilePath(AdBlock::AdblockUtil::localFilterPath());
}

void AdBlockCustomList::loadSubscription(const QStringList &disabledRules)
{
    // DuckDuckGo ad whitelist rules
    // They cannot be removed, but can be disabled.
    // Please consider not disabling them. Thanks!

    const QString ddg1 = QStringLiteral("@@||duckduckgo.com^$document");
    const QString ddg2 = QStringLiteral("duckduckgo.com#@#.has-ad");

    const QString rules = QString::fromUtf8(readAllFileByteContents(filePath()));

    QFile file(filePath());
    if (!file.exists()) {
        saveSubscription();
    }

    if (file.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream stream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        stream.setCodec("UTF-8");
#endif

        if (!rules.contains(ddg1 + QLatin1Char('\n'))) {
            stream << ddg1 << QLatin1Char('\n');
        }

        if (!rules.contains(QLatin1Char('\n') + ddg2)) {
            stream << ddg2 << QLatin1Char('\n');
        }
    }
    file.close();

    AdBlockSubscription::loadSubscription(disabledRules);
}

QByteArray AdBlockCustomList::readAllFileByteContents(const QString &filename)
{
    QFile file(filename);

    if (!filename.isEmpty() && file.open(QFile::ReadOnly)) {
        const QByteArray a = file.readAll();
        file.close();
        return a;
    }

    return {};
}

void AdBlockCustomList::saveSubscription()
{
    QFile file(filePath());

    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for writing:" << filePath();
        return;
    }

    QTextStream textStream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    textStream.setCodec("UTF-8");
#endif

    textStream << "Title: " << title() << QLatin1Char('\n');
    textStream << "Url: " << url().toString() << QLatin1Char('\n');
    textStream << "[Adblock Plus 1.1.1]" << QLatin1Char('\n');

    for (const AdBlockRule *rule : std::as_const(mRules)) {
        textStream << rule->filter() << QLatin1Char('\n');
    }

    file.close();
}

bool AdBlockCustomList::canEditRules() const
{
    return true;
}

bool AdBlockCustomList::canBeRemoved() const
{
    return false;
}

bool AdBlockCustomList::containsFilter(const QString &filter) const
{
    for (const AdBlockRule *rule : std::as_const(mRules)) {
        if (rule->filter() == filter) {
            return true;
        }
    }

    return false;
}

bool AdBlockCustomList::removeFilter(const QString &filter)
{
    const int numberRules(mRules.count());
    for (int i = 0; i < numberRules; ++i) {
        const AdBlockRule *rule = mRules.at(i);

        if (rule->filter() == filter) {
            return removeRule(i);
        }
    }

    return false;
}

int AdBlockCustomList::addRule(AdBlockRule *rule)
{
    mRules.append(rule);

    Q_EMIT subscriptionChanged();

    return mRules.count() - 1;
}

bool AdBlockCustomList::removeRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return false;
    }

    AdBlockRule *rule = mRules.at(offset);
    const QString filter = rule->filter();

    mRules.remove(offset);

    Q_EMIT subscriptionChanged();

    AdblockManager::self()->removeDisabledRule(filter);

    delete rule;
    return true;
}

const AdBlockRule *AdBlockCustomList::replaceRule(AdBlockRule *rule, int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *oldRule = mRules.at(offset);
    mRules[offset] = rule;

    Q_EMIT subscriptionChanged();

    delete oldRule;
    return mRules[offset];
}
