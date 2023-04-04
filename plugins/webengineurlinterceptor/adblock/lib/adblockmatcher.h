/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   This file originates from QupZilla - WebKit based browser
   SPDX-FileCopyrightText: 2014 David Rosca <nowrep@gmail.com>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockrule.h"
#include "adblocksearchtree.h"
#include <QList>
#include <QObject>
#include <QUrl>

class QWebEngineUrlRequestInfo;

namespace AdBlock
{
class AdblockManager;
class AdBlockMatcher : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockMatcher(AdblockManager *manager);
    ~AdBlockMatcher() override;

    const AdBlockRule *match(const QWebEngineUrlRequestInfo &request, const QString &urlDomain, const QString &urlString) const;

    Q_REQUIRED_RESULT bool adBlockDisabledForUrl(const QUrl &url) const;
    Q_REQUIRED_RESULT bool elemHideDisabledForUrl(const QUrl &url) const;

    QString elementHidingRules() const;
    QString elementHidingRulesForDomain(const QString &domain) const;

    bool isEnabled() const;

public Q_SLOTS:
    void update();
    void clear();

private:
    void enabledChanged(bool enabled);
    AdblockManager *mManager = nullptr;

    QList<AdBlockRule *> mCreatedRules;
    QList<const AdBlockRule *> mNetworkExceptionRules;
    QList<const AdBlockRule *> mNetworkBlockRules;
    QList<const AdBlockRule *> mDomainRestrictedCssRules;
    QList<const AdBlockRule *> mDocumentRules;
    QList<const AdBlockRule *> mElemhideRules;

    QString mElementHidingRules;
    AdBlockSearchTree mNetworkBlockTree;
    AdBlockSearchTree mNetworkExceptionTree;
    bool mEnabled = false;
};
}
