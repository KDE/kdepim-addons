/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKMANAGER_H
#define ADBLOCKMANAGER_H

#include <QObject>
#include <QWebEngineUrlRequestInfo>
#include "adblocklib_export.h"
namespace AdBlock {
class AdBlockMatcher;
class AdBlockSubscription;
class AdBlockCustomList;
class ADBLOCKLIB_EXPORT AdblockManager : public QObject
{
    Q_OBJECT
public:
    static AdblockManager *self();
    explicit AdblockManager(QObject *parent = nullptr);
    ~AdblockManager();
    bool isEnabled() const;

    bool interceptRequest(const QWebEngineUrlRequestInfo &info);

    QList<AdBlockSubscription *> subscriptions() const;

    void addDisabledRule(const QString &str);
    void removeDisabledRule(const QString &filter);

    void save();

    Q_REQUIRED_RESULT QStringList disabledRules() const;

    void updateAllSubscriptions();

    AdBlockSubscription *addSubscription(const QString &title, const QString &url);

    Q_REQUIRED_RESULT bool removeSubscription(AdBlockSubscription *subscription);
    void addCustomRule(const QString &filter);
Q_SIGNALS:
    void enabledChanged(bool);

public Q_SLOTS:
    void reloadConfig();

private:
    void updateMatcher();
    void loadSubscriptions();
    bool canRunOnScheme(const QString &scheme) const;
    bool mEnabled;
    AdBlockMatcher *mAdBlockMatcher = nullptr;
    QStringList mDisabledRules;
    QList<AdBlockSubscription *> mSubscriptions;
    AdBlockCustomList *mCustomList = nullptr;
};
}
#endif // ADBLOCKMANAGER_H
