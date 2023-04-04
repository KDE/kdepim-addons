/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   This file originates from QupZilla - WebKit based browser
   SPDX-FileCopyrightText: 2014 David Rosca <nowrep@gmail.com>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmatcher.h"
#include "adblockmanager.h"
#include "adblocksubscription.h"

using namespace AdBlock;
AdBlockMatcher::AdBlockMatcher(AdblockManager *manager)
    : QObject(manager)
    , mManager(manager)
{
    connect(manager, &AdblockManager::enabledChanged, this, &AdBlockMatcher::enabledChanged);
}

AdBlockMatcher::~AdBlockMatcher()
{
    clear();
}

const AdBlockRule *AdBlockMatcher::match(const QWebEngineUrlRequestInfo &request, const QString &urlDomain, const QString &urlString) const
{
    // Exception rules
    if (mNetworkExceptionTree.find(request, urlDomain, urlString)) {
        return nullptr;
    }

    int count = mNetworkExceptionRules.count();
    for (int i = 0; i < count; ++i) {
        const AdBlockRule *rule = mNetworkExceptionRules.at(i);
        if (rule->networkMatch(request, urlDomain, urlString)) {
            return nullptr;
        }
    }

    // Block rules
    if (const AdBlockRule *rule = mNetworkBlockTree.find(request, urlDomain, urlString)) {
        return rule;
    }

    count = mNetworkBlockRules.count();
    for (int i = 0; i < count; ++i) {
        const AdBlockRule *rule = mNetworkBlockRules.at(i);
        if (rule->networkMatch(request, urlDomain, urlString)) {
            return rule;
        }
    }

    return nullptr;
}

bool AdBlockMatcher::adBlockDisabledForUrl(const QUrl &url) const
{
    const int count = mDocumentRules.count();

    for (int i = 0; i < count; ++i) {
        if (mDocumentRules.at(i)->urlMatch(url)) {
            return true;
        }
    }

    return false;
}

bool AdBlockMatcher::elemHideDisabledForUrl(const QUrl &url) const
{
    if (adBlockDisabledForUrl(url)) {
        return true;
    }

    const int count = mElemhideRules.count();

    for (int i = 0; i < count; ++i) {
        if (mElemhideRules.at(i)->urlMatch(url)) {
            return true;
        }
    }

    return false;
}

QString AdBlockMatcher::elementHidingRules() const
{
    return mElementHidingRules;
}

QString AdBlockMatcher::elementHidingRulesForDomain(const QString &domain) const
{
    QString rules;
    int addedRulesCount = 0;
    const int count = mDomainRestrictedCssRules.count();

    for (int i = 0; i < count; ++i) {
        const AdBlockRule *rule = mDomainRestrictedCssRules.at(i);
        if (!rule->matchDomain(domain)) {
            continue;
        }

        if (Q_UNLIKELY(addedRulesCount == 1000)) {
            rules.append(rule->cssSelector());
            rules.append(QLatin1String("{display:none !important;}\n"));
            addedRulesCount = 0;
        } else {
            rules.append(rule->cssSelector() + QLatin1Char(','));
            addedRulesCount++;
        }
    }

    if (addedRulesCount != 0) {
        rules = rules.left(rules.size() - 1);
        rules.append(QStringLiteral("{display:none !important;}\n"));
    }

    return rules;
}

bool AdBlockMatcher::isEnabled() const
{
    return mEnabled;
}

void AdBlockMatcher::update()
{
    clear();

    QHash<QString, const AdBlockRule *> cssRulesHash;
    QList<const AdBlockRule *> exceptionCssRules;
    const auto subscriptions = mManager->subscriptions();
    for (AdBlockSubscription *subscription : subscriptions) {
        for (const AdBlockRule *rule : subscription->allRules()) {
            // Don't add internally disabled rules to cache
            if (rule->isInternalDisabled()) {
                continue;
            }

            if (rule->isCssRule()) {
                // We will add only enabled css rules to cache, because there is no enabled/disabled
                // check on match. They are directly embedded to pages.
                if (!rule->isEnabled()) {
                    continue;
                }

                if (rule->isException()) {
                    exceptionCssRules.append(rule);
                } else {
                    cssRulesHash.insert(rule->cssSelector(), rule);
                }
            } else if (rule->isDocument()) {
                mDocumentRules.append(rule);
            } else if (rule->isElemhide()) {
                mElemhideRules.append(rule);
            } else if (rule->isException()) {
                if (!mNetworkExceptionTree.add(rule)) {
                    mNetworkExceptionRules.append(rule);
                }
            } else {
                if (!mNetworkBlockTree.add(rule)) {
                    mNetworkBlockRules.append(rule);
                }
            }
        }
    }

    for (const AdBlockRule *rule : std::as_const(exceptionCssRules)) {
        const AdBlockRule *originalRule = cssRulesHash.value(rule->cssSelector());

        // If we don't have this selector, the exception does nothing
        if (!originalRule) {
            continue;
        }

        AdBlockRule *copiedRule = originalRule->copy();
        copiedRule->m_options |= AdBlockRule::DomainRestrictedOption;
        copiedRule->m_blockedDomains.append(rule->m_allowedDomains);

        cssRulesHash[rule->cssSelector()] = copiedRule;
        mCreatedRules.append(copiedRule);
    }

    // Apparently, excessive amount of selectors for one CSS rule is not what WebKit likes.
    // (In my testings, 4931 is the number that makes it crash)
    // So let's split it by 1000 selectors...
    int hidingRulesCount = 0;

    QHashIterator<QString, const AdBlockRule *> it(cssRulesHash);
    while (it.hasNext()) {
        it.next();
        const AdBlockRule *rule = it.value();

        if (rule->isDomainRestricted()) {
            mDomainRestrictedCssRules.append(rule);
        } else if (Q_UNLIKELY(hidingRulesCount == 1000)) {
            mElementHidingRules.append(rule->cssSelector());
            mElementHidingRules.append(QStringLiteral("{display:none !important;} "));
            hidingRulesCount = 0;
        } else {
            mElementHidingRules.append(rule->cssSelector() + QLatin1Char(','));
            hidingRulesCount++;
        }
    }

    if (hidingRulesCount != 0) {
        mElementHidingRules = mElementHidingRules.left(mElementHidingRules.size() - 1);
        mElementHidingRules.append(QLatin1String("{display:none !important;} "));
    }
}

void AdBlockMatcher::clear()
{
    mNetworkExceptionTree.clear();
    mNetworkExceptionRules.clear();
    mNetworkBlockTree.clear();
    mNetworkBlockRules.clear();
    mDomainRestrictedCssRules.clear();
    mElementHidingRules.clear();
    mDocumentRules.clear();
    mElemhideRules.clear();
    qDeleteAll(mCreatedRules);
    mCreatedRules.clear();
}

void AdBlockMatcher::enabledChanged(bool enabled)
{
    mEnabled = enabled;
    if (mEnabled) {
        update();
    } else {
        clear();
    }
}
