/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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
