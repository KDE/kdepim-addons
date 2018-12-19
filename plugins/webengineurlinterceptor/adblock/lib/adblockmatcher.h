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

/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef ADBLOCKMATCHER_H
#define ADBLOCKMATCHER_H

#include <QUrl>
#include <QObject>
#include <QVector>
#include "adblockrule.h"
#include "adblocksearchtree.h"

class QWebEngineUrlRequestInfo;

namespace AdBlock {
class AdblockManager;
class AdBlockMatcher : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockMatcher(AdblockManager *manager);
    ~AdBlockMatcher();

    const AdBlockRule *match(const QWebEngineUrlRequestInfo &request, const QString &urlDomain, const QString &urlString) const;

    bool adBlockDisabledForUrl(const QUrl &url) const;
    bool elemHideDisabledForUrl(const QUrl &url) const;

    QString elementHidingRules() const;
    QString elementHidingRulesForDomain(const QString &domain) const;

    bool isEnabled() const;

public Q_SLOTS:
    void update();
    void clear();

private:
    void enabledChanged(bool enabled);
    AdblockManager *mManager = nullptr;

    QVector<AdBlockRule *> mCreatedRules;
    QVector<const AdBlockRule *> mNetworkExceptionRules;
    QVector<const AdBlockRule *> mNetworkBlockRules;
    QVector<const AdBlockRule *> mDomainRestrictedCssRules;
    QVector<const AdBlockRule *> mDocumentRules;
    QVector<const AdBlockRule *> mElemhideRules;

    QString mElementHidingRules;
    AdBlockSearchTree mNetworkBlockTree;
    AdBlockSearchTree mNetworkExceptionTree;
    bool mEnabled = false;
};
}

#endif // ADBLOCKMATCHER_H
